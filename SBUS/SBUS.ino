#include "SBUS.hpp"
SBUS propo;

void setup()
{
    propo.init();
    Serial.begin(57600);
}

void loop()
{
    propo.readData();

    for (int i = 0; i < 4; i++)
    {
        Serial.print(propo.getStickVal(i));
        Serial.print("\t");
    }

    for (int i = 0; i < 5; i++)
    {
        Serial.print(propo.getSwitchVal(i));
        Serial.print("\t");
    }
    Serial.println();
}
