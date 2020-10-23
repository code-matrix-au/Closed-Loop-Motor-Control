#include <MetroDoor.h>

MetroDoor ::MetroDoor(int pin)
{
    door.attach(pin);
    door_state_closed = false;
    door_state_opened = false;
}

bool MetroDoor::close()
{
    if (door_state_closed == true)
    {
        door.writeMicroseconds(1500);
        return true;
    }

    if (last_closed_state == 0)
    {
        time.reset();
        last_closed_state = 1;
        door.writeMicroseconds(2000);
    }

    if (time.check() == 1)
    {
        door_state_closed = true;
    }
    return false;
}

bool MetroDoor::open()
{
    if (door_state_opened == true)
    {
        door.writeMicroseconds(1500);
        return true;
    }

    if (last_opened_state == 0)
    {
        time.reset();
        last_opened_state = 1;
        door.writeMicroseconds(1000);
    }

    if (time.check() == 1)
    {
        door_state_opened = true;
    }
    return false;
}