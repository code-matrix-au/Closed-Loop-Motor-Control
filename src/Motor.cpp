#include <Arduino.h>
#include <Encoder.h>
#include <Metro.h>
#include <PID_v1.h>
#include <Servo.h>
#include "Motor.h"

double Setpoint, Input, Output;

double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp = 1, consKi = 0.05, consKd = 0.25;

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

Servo servoMotor;

Encoder myEnc(22, 23);

long oldPosition = -999;

Metro timer = Metro(0);

int state = HIGH;


Motor :: Motor(){
this->PWM=0;

}

void Motor::getInterupt(){
    long newPosition = myEnc.read();
     if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Input =newPosition;
     }
}




void Motor::myloop()
{

}

void Motor ::emergencyStop()
{
}

void Motor ::init()
{
    servoMotor.attach(13);
    myPID.SetMode(AUTOMATIC);
}

void Motor ::setSpeed(long val)
{
    this->speed = val;
    myloop();
}


int setFreq(int val)
{
    
  
  while (PWM != val)
  {
    if (timer.check() == 1)
    {
      if (state == true)
      {
        state = false;
        timer.interval(25);
        PWM++;
        return PWM;
      }
      else
      {
        timer.interval(25);
        state = true;
      }
    }
    return -1;
  }
}




void Motor ::setDistance(long pos)
{
    this->location = pos;
    double gap = abs(pos - Input);
  
    if (gap > 50)
    {
        Setpoint = pos;
        myPID.SetTunings(consKp, consKi, consKd);
        myPID.Compute();
      //  servoMotor.write(out);
    }
    else
    {
       servoMotor.writeMicroseconds(1500);
    }
}