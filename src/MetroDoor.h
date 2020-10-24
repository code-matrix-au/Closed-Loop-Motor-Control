#include <Metro.h>
#include <Servo.h>
#include <Arduino.h>

class MetroDoor

{
    Servo door;
    Metro time = Metro(5000);

public:
    MetroDoor(int);
    bool open();
    bool close();
    void compute(int);

private:
    bool closed;
    bool opened;
    int state;
    int hook;
};
