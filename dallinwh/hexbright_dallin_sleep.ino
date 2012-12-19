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
  pinMode(DPIN_PWR,      INPUT);
  digitalWrite(DPIN_PWR, LOW);

  // Initialize GPIO
  pinMode(DPIN_RLED_SW,  INPUT);
  pinMode(DPIN_GLED,     OUTPUT);
  pinMode(DPIN_DRV_MODE, OUTPUT);
  pinMode(DPIN_DRV_EN,   OUTPUT);
  digitalWrite(DPIN_DRV_MODE, LOW);
  digitalWrite(DPIN_DRV_EN,   LOW);
  digitalWrite(DPIN_GLED, HIGH);
 
  btnDown = digitalRead(DPIN_RLED_SW);
  btnTime = millis();
  lastTime = millis();
  counter = 0;
}

void loop()
{
  unsigned long time = millis();
  boolean newBtnDown = digitalRead(DPIN_RLED_SW);
 
  if (btnDown && !newBtnDown && (time-btnTime)>50) {
    if (counter <= time){
      counter = time + 30000;
    } else {
      counter += 30000;
    }
  }

  if (btnDown && time-btnTime>500){
    counter = 0;
  }

  if (counter > time) {
    pinMode(DPIN_PWR,      OUTPUT);
    digitalWrite(DPIN_PWR, HIGH);
    digitalWrite(DPIN_DRV_EN, HIGH);
  } else {
    pinMode(DPIN_PWR,      OUTPUT);
    digitalWrite(DPIN_PWR, LOW);
    digitalWrite(DPIN_DRV_EN, LOW);
  }
 
  if (newBtnDown != btnDown)
  {
    btnTime = time;
    btnDown = newBtnDown;
    delay(50);
  }
  lastTime = time;
}

