#include <Arduino.h>
#include "Motor.h"

Motor metro = Motor();

/*
int setPWM(int val)
{
  
  while (PWM != val)
  {

    if (timer.check() == 1)
    {
      if (state == HIGH)
      {
        state = LOW;
        timer.interval(25);
        PWM++;
        return PWM;
      }
      else
      {
        timer.interval(25);
        state = HIGH;
      }
    }
    return -999;
  }
}


*/
void setup()
{
  metro.init();
  Serial.begin(115200);
}

void loop()
{
  // metro.setSpeed(100);
  
   metro.getInterupt();
   metro.setDistance(999);

 //  metro.emergencyStop();
}
