#include <Arduino.h>
#include <Encoder.h>
#include <Metro.h>
#include <PID_v1.h>
#include <Servo.h>

double Setpoint, Input, Output;

double consKp = 0.05, consKi = 0, consKd = 0.05;

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

Servo motor;

Encoder myEnc(22, 23);

long oldPosition = -999;

void setup()
{
  motor.attach(13);
  myPID.SetOutputLimits(0,500);
  myPID.SetMode(AUTOMATIC);
  Serial.begin(115200);
}

void loop()
{

  long newPosition = myEnc.read();
  if (newPosition != oldPosition)
  {
    oldPosition = newPosition;
    Input = newPosition;
  }

  myPID.Compute();
  double gap = (Setpoint - Input);
  int out;
  if (gap < 0)
  {
    myPID.SetControllerDirection(REVERSE);
    out = map(Output, 0, 500, 1500, 1000);
  }
  else
  {
    myPID.SetControllerDirection(DIRECT);
    out = map(Output, 0, 500, 1500, 2000);
  }
  motor.write(out);
  Serial.print(Input);
  Serial.print("  ");
  Serial.println(out);
}
