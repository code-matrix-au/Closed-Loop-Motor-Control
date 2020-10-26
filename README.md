# MetroDoor library.

#include <MetroDoor.h>

MetroDoor mydoor(13); // value input is for the pin the door is attached on the arduino.

mydoor.open(); // will open the door
mydoor.close();// will close the door
Serial.println(mydoor.close()); // the output return will be 0 until the door is closed and it will return 1.


while(mydoor.open() != true){
    Serial.println(" the door is still opening");
    return;
}

# Motor  library

#include <motor.h>

Motor mymotor(13); // pin connected to the motor on the arduino

mymotor.Dir_Speed(1,255);   // set the dirrection 1 or -1 and 0,255 is the speed.

mymotor.Stop(); stops the motor from the current speed. Returns true when the motor has completely stopped.

mymotor.start() starts the motor. returns true when motor has reached set speed.

mymotor.SetDIstance(10000); it will use PID to reach that set pint of 10000 rotations.



