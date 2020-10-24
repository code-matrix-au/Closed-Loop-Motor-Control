#include <MetroDoor.h>

MetroDoor ::MetroDoor(int pin)
{
    door.attach(pin);
    closed = false;
    opened = false;
    state = 0;
    hook = 0;
}

bool MetroDoor::open()
{
    if (opened == true)
    {
        return true;
    }
    compute(1);
    return false;
}

bool MetroDoor::close()
{
    if (closed == true)
    {
        return true;
    }
    compute(-1);
    return false;
}

void MetroDoor::compute(int val) // 1 = open; -1 = close;
{
    if (val == 1 && state == 0)
    {
        time.reset();
        state = 1;
        hook = val;
        door.writeMicroseconds(1700);
    }
    else if (val == -1 && state == 0)
    {
        time.reset();
        state = 1;
        hook = val;
        door.writeMicroseconds(1300);
    }

    if (time.check() == 1)
    {
        state = 0;
        door.writeMicroseconds(1500);
        if (hook == 1)
        {
            opened = true;
            closed = false;
        }
        else if (hook == -1)
        {
            closed = true;
            opened = false;
        }
        return;
    }
}
