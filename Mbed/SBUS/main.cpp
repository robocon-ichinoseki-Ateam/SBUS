#include "mbed.h"
#include "SBUS.hpp"
SBUS propo(PA_9, PA_10);
Serial pc(USBTX, USBRX);

int main()
{
    pc.baud(57600);
    while(1) {
        for (int i = 0; i < 4; i++)
            pc.printf("%d\t", propo.getStickVal(i));

        for (int i = 0; i < 5; i++)
            pc.printf("%d\t", propo.getSwitchVal(i));

        pc.printf("\n");
    }
}