/*
  Hexbright firmware: Sleep
  Dallin Wheeler  11/2012
 
  Every button press adds 30 seconds to the lights running time.
*/

// Pin assignments
#define DPIN_RLED_SW            2
#define DPIN_GLED               5
#define DPIN_PWR                8
#define DPIN_DRV_MODE           9
#define DPIN_DRV_EN             10
// Modes
#define MODE_OFF                0
#define MODE_ON                 1

byte mode;
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
 
  mode = MODE_OFF;
  btnDown = digitalRead(DPIN_RLED_SW);
  btnTime = millis();
}

void loop()
{
  unsigned long time = millis();
  boolean newBtnDown = digitalRead(DPIN_RLED_SW);
 
  if (newBtnDown) {
    counter += 30000;
    digitalWrite(DPIN_DRV_EN, HIGH);
  }
  if (time-lastTime >= 100 && counter != 0){
    if(time-lastTime >= counter) {
      counter = 0;
      digitalWrite(DPIN_DRV_EN, LOW);
    } else {
      counter -= (time-lastTime);
    }
  }
  if (btnDown && newBtnDown && time-btnTime>200){
    counter = 0;
    digitalWrite(DPIN_DRV_EN, LOW);
  }
 
  if (newBtnDown != btnDown)
  {
    btnTime = time;
    btnDown = newBtnDown;
    delay(50);
  }
}
