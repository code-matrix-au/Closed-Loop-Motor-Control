#include "Motor.h"
/*
Motor ::Motor()
{
    oldPosition = -999;
    motorOut = 1500;
    doorState = false;
    stopState = HIGH;
    motor.attach(13);
    door.attach(12);
    myEnc(22,23);
    double consKp = 0.1, consKi = 0.0001, consKd = 0.2;
    PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
  //  Metro metroStop = Metro(0);
  //  Metro doorTime = Metro(0);
    
}

void Motor ::Stop()
{
    if (motorOut != 1500)
  {
    int val;

    if (motorOut > 1500)
    {
      val = -1;
    }
    else if (motorOut < 1500)
    {
      val = 1;
    }
    else
    {
      val = 0;
    }

    if (metroStop.check() == 1) // check if the metro has passed its interval .
    {
      if (stopState == HIGH)
      {
        stopState = LOW;
        motorOut = +val;
      }
      else
      {
        stopState = HIGH;
      }
      motor.write(motorOut);
    }
  }
}

void Motor ::Forward()
{
}

void Motor ::Reverse()
{
}

void Motor ::SetDistance()
{
}

void Motor::Setspeed()
{
}
*/