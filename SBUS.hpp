// Cf:http://zeemo4275.hatenablog.com/entry/2017/10/04/153251

#ifndef _SBUS_
#define _SBUS_

#include <Arduino.h>

#define SBUS_SYNCBYTE 0x0F

class SBUS
{
public:
  void init();
  void readData();
  int16_t getData(uint8_t ch);
  bool isFailSafe();
  int getStickVal(int axis);
  int getSwitchVal(int parm);

private:
  bool failSafe = true;
  unsigned int chData[18] = {0};
  unsigned int dataIndex = 0;
};

#endif