# MetroDoor library.

#include <MetroDoor.h>

MetroDoor mydoor(13); // value input is for the pin the door is atached on the arduino.

mydoor.open(); // will open the door
mydoor.close();// will close the door
Serial.println(mydoor.close()); // the output return will be 0 until the door is closed and it will return 1.


while(mydoor.open() != true){
    Serial.println(" the door is still opening");
    return;
}

# Motor  library

