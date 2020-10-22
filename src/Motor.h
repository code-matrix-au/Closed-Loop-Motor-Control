#include <Arduino.h>
#include <Encoder.h>
#include <Metro.h>
#include <PID_v1.h>
#include <Servo.h>

class Motor
{

    struct state
    {
        /* data */
    };

    typedef enum
    {
        STOP,
        START,
        EAST,
        WEST,
        OPEN,
        CLOSE,
        EMERGENCY
    } trainstate;

public:
    Motor();
    void Stop();
    void Setspeed();
    void SetDistance();
    void Forward();
    void Reverse();

private:
    double Setpoint;
    double Input;
    double Output;
    long motorOut;
    long oldPosition;
    long disthold;
    bool doorState;
    int stopState;
    Servo motor;
    Servo door;
    Encoder myEnc(int, int);
    Metro metroStop; 
    Metro doorTime; 

   
};