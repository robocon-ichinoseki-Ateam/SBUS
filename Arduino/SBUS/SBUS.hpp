// Cf:http://zeemo4275.hatenablog.com/entry/2017/10/04/153251

#ifndef _SBUS_
#define _SBUS_

#include <Arduino.h>

#define SBUS_PORT Serial1
#define SBUS_SYNCBYTE 0x0F

class SBUS
{
  public:
    unsigned int rcChannel[18] = {0};
    unsigned int sbusIndex = 0;

    void init();
    void readData();
    int16_t getData(uint8_t ch);
    int getStickVal(int axis);
    int getSwitchVal(int parm);
};
#endif