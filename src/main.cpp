#include <Arduino.h>
#include <Encoder.h>
#include <Metro.h>
#include <PID_v1.h>
#include <Servo.h>

double Setpoint, Input, Output;

double consKp = 0.1, consKi = 0.0001, consKd = 0.2;

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

Servo motor;
Servo door;
Encoder myEnc(22, 23);

Metro metroStop = Metro(50);
Metro doorTime = Metro(100);
Metro print_val = Metro(100);
int print_state = HIGH;
struct Value
{
  long oldPosition;
  long distance;
  int stopState;
  int doorlock;
  unsigned int motorOut;
  bool doorState;
  bool metro_stopped;
  int lastState;
  Metro ramp_up;
  int ramp_state;

} value = {
    -999,  // oldPosition
    0,     // distance
    HIGH,  // stopState
    LOW,   // doorlock
    1500,  // motorOut
    false, // doorState
    false, // metro_stopped
    0,
    50,
    HIGH}; // lastState

enum State
{
  STOP,
  START,
  EAST,
  WEST,
  OPEN,
  CLOSE,
  EMERGENCY
} state;

void Stop()
{

  if (value.motorOut != 1500)
  {
    value.metro_stopped = false;
    int val;

    if (value.motorOut > 1500)
    {
      val = -10;
    }
    else if (value.motorOut < 1500)
    {
      val = 10;
    }
    else
    {
      val = 0;
    }

    if (metroStop.check() == 1) // check if the metro has passed its interval .
    {
      if (value.stopState == HIGH)
      {
        value.stopState = LOW;
      }
      else
      {
        value.stopState = HIGH;
      }
      value.motorOut += val;
      motor.write(value.motorOut);
      //Serial.println(value.motorOut);
    }
  }
  value.metro_stopped = true;
}

void setDistance(long var)
{
  if (var != Setpoint)
  { // checks if we received new value and updates setpoint.
    Setpoint = var;
  }
  int out;
  double gap = (Setpoint - Input);
  if (gap < 0)
  {
    myPID.SetControllerDirection(REVERSE);
    out = map(Output, 0, 500, 1500, 2000);
  }
  else
  {
    myPID.SetControllerDirection(DIRECT);
    out = map(Output, 0, 500, 1500, 1000);
  }
  myPID.Compute();
  value.motorOut = out;
  motor.write(value.motorOut);
}

void metroDoor(int pos)
{

  if (pos == 1 && value.doorState == false)
  {
    if (doorTime.check() == 1) // check if the metro has passed its interval .
    {
      if (value.doorlock == HIGH)
      {
        value.doorlock = LOW;
      }
      else
      {
        value.doorlock = HIGH;
      }
      door.writeMicroseconds(1250);
      value.doorState = true;
    }
    else if (pos == 0 and value.doorState == true)
    { // open door
      value.doorState = false;
    }
  }
}

void direction(int dir, int speed)
{

  if (dir > 0 && value.lastState == 0) // this part takes care of the dirrection change of the motor.
  {
    Stop();

    if (value.motorOut != 1500)
    {
      return;
    }
    value.lastState = 1;
  }
  else if (dir < 0 && value.lastState == 1)
  {
    Stop();

    if (value.motorOut != 1500)
    {
      return;
    }
    value.lastState = 0;
  }
  else
  {
    int my_dir;
    int newspeed;

    if (dir > 0)
    {
      newspeed = map(speed, 0, 255, 1500, 2000);
      my_dir = 5;
    }
    else if (dir < 0)
    {
      newspeed = map(speed, 0, 255, 1500, 1000);
      my_dir = -5;
    }

    if (value.ramp_up.check() == 1) // check if the metro has passed its interval .
    {
      if (value.ramp_state == HIGH)
      {
        value.ramp_state = LOW;
      }
      else
      {
        value.stopState = HIGH;
      }

      if (value.motorOut != newspeed)
      {
        value.motorOut += my_dir;
      }
      motor.write(value.motorOut);
    }
  }
}

void print_data()
{

  if (print_val.check() == 1) // check if the metro has passed its interval .
  {
    if (print_state == HIGH)
    {
      print_state = LOW;
    }
    else
    {
      print_state = HIGH;
    }
    Serial.print("MotorOut");
    Serial.print("  ");
    Serial.println(value.motorOut);
  }
}

void setup()
{
  motor.attach(13);
  door.attach(12);
  myPID.SetOutputLimits(0, 500);
  myPID.SetMode(AUTOMATIC);
  Serial.begin(115200);
  value.motorOut = 2000;
}

void loop()
{

  switch (state)
  {
  case STOP:
    direction(1, 1750);
    print_data();
    // Stop();
    // Serial.println("STOP");
    break;
  case START:
    Serial.println("START");
    // Start();
    break;
  case EAST:
    direction(1, 200); // 1 to move EAST and 200 is the set speed
    Serial.println("EAST");
    break;
  case WEST:
    direction(-1, 200); //-1 to move WEST and 200 is the set speed
    Serial.println("WEST");
    break;
  case OPEN:
    metroDoor(1); // '1' to open door and '0' to close
    Serial.println("OPEN");
    break;
  case CLOSE:
    metroDoor(0); // '1' to open door and '0' to close
    Serial.println("CLOSE");
    break;
  case EMERGENCY:
    // do something
    motor.writeMicroseconds(1500);
    Serial.println("EMERGENCY");
    break;
  }

  long newPosition = myEnc.read();
  if (newPosition != value.oldPosition)
  {
    value.oldPosition = newPosition;
    Input = newPosition;
  }
}
