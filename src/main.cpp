#include <Arduino.h>
#include <Motor.h>
#include <MetroDoor.h>

MetroDoor mydoor(12);
Motor mymotor(13);

void setup()
{
 Serial.begin(9600);
}

void loop()
{
  mymotor.Dir_Speed(1,255);
  mymotor.Start();
  

}


/*

  long newPosition = myEnc.read();
  if (newPosition != value.oldPosition)
  {
    value.oldPosition = newPosition;
    Input = newPosition;
  }

*/