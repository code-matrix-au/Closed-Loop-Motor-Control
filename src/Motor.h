#include <spi.h>
class Motor
{

public:
Motor();
void init();
void myloop();
void getInterupt();
void emergencyStop();
void setSpeed(long);
void setDistance(long);
int setFreq(int);

private:
long speed;
long location;
long counter;
int PWM;
boolean state;
};




