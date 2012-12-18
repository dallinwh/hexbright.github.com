/*
  Hexbright firmware: Sleep
  Dallin Wheeler  11/2012
 
  Every button press adds 30 seconds to the lights running time.
*/

#include <Wire.h>

// Pin assignments
#define DPIN_RLED_SW            2
#define DPIN_GLED               5
#define DPIN_PWR                8
#define DPIN_DRV_MODE           9
#define DPIN_DRV_EN             10

boolean btnDown;
unsigned long lastTime, btnTime, counter;

void setup()
{
  pinMode(DPIN_PWR,      OUTPUT);
  digitalWrite(DPIN_PWR, HIGH);

  // Initialize GPIO
  pinMode(DPIN_RLED_SW,  INPUT);
  pinMode(DPIN_GLED,     OUTPUT);
  pinMode(DPIN_DRV_MODE, OUTPUT);
  pinMode(DPIN_DRV_EN,   OUTPUT);
  digitalWrite(DPIN_DRV_MODE, LOW);
  digitalWrite(DPIN_DRV_EN,   LOW);
  digitalWrite(DPIN_GLED, HIGH);
 
   // Initialize serial busses
  Serial.begin(9600);
  Wire.begin();
 
  btnDown = digitalRead(DPIN_RLED_SW);
  btnTime = millis();
  lastTime = millis();
  counter = 0;
}

void loop()
{
  unsigned long time = millis();
  boolean newBtnDown = digitalRead(DPIN_RLED_SW);
 
  if (newBtnDown) {
    if (counter < time){
      counter = time + 30000;
    } else {
      counter += 30000;
    }
  }
  
  Serial.print(time);
  Serial.print(' ');
  Serial.println(counter);

  if (btnDown && newBtnDown && time-btnTime>200){
    counter = 0;
  }

  if (counter > time) {
    digitalWrite(DPIN_DRV_EN, HIGH);
  } else {
    digitalWrite(DPIN_DRV_EN, LOW);
  }
 
  if (newBtnDown != btnDown)
  {
    btnTime = time;
    btnDown = newBtnDown;
    delay(200);
  }
  lastTime = time;
}
