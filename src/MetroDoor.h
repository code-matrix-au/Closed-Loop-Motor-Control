
#include <Metro.h>
#include <Servo.h>
#include <Arduino.h>

class MetroDoor

{

public:
    MetroDoor(int);
    bool open();
    bool close();

private:
    bool door_state_closed;
    bool door_state_opened;
    int last_closed_state;
    int last_opened_state;
    Servo door;
    Metro time = Metro(5000);
};
