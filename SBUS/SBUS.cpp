#include "SBUS.hpp"

void SBUS::init()
{
    // スタート1、データ8、パリティ1、ストップ2
    SBUS_PORT.begin(100000, SERIAL_8E2);
}

void SBUS::readData()
{
    static uint8_t sbus[25] = {0};
    while (SBUS_PORT.available())
    {
        int val = SBUS_PORT.read();

        if (sbusIndex == 0 && val != SBUS_SYNCBYTE)
        {
            continue;
        }

        sbus[sbusIndex] = val;
        sbusIndex++;
        if (sbusIndex == 25)
        {
            sbusIndex = 0;

            if (sbus[24] != 0x0)
            {
                rcChannel[0] = ((sbus[1] | sbus[2] << 8) & 0x07FF);
                rcChannel[1] = ((sbus[2] >> 3 | sbus[3] << 5) & 0x07FF);
                rcChannel[2] = ((sbus[3] >> 6 | sbus[4] << 2 | sbus[5] << 10) & 0x07FF);
                rcChannel[3] = ((sbus[5] >> 1 | sbus[6] << 7) & 0x07FF);
                rcChannel[4] = ((sbus[6] >> 4 | sbus[7] << 4) & 0x07FF);
                rcChannel[5] = ((sbus[7] >> 7 | sbus[8] << 1 | sbus[9] << 9) & 0x07FF);
                rcChannel[6] = ((sbus[9] >> 2 | sbus[10] << 6) & 0x07FF);
                rcChannel[7] = ((sbus[10] >> 5 | sbus[11] << 3) & 0x07FF);
                rcChannel[8] = ((sbus[12] | sbus[13] << 8) & 0x07FF);
                rcChannel[9] = ((sbus[13] >> 3 | sbus[14] << 5) & 0x07FF);
                rcChannel[10] = ((sbus[14] >> 6 | sbus[15] << 2 | sbus[16] << 10) & 0x07FF);
                rcChannel[11] = ((sbus[16] >> 1 | sbus[17] << 7) & 0x07FF);
                rcChannel[12] = ((sbus[17] >> 4 | sbus[18] << 4) & 0x07FF);
                rcChannel[13] = ((sbus[18] >> 7 | sbus[19] << 1 | sbus[20] << 9) & 0x07FF);
                rcChannel[14] = ((sbus[20] >> 2 | sbus[21] << 6) & 0x07FF);
                rcChannel[15] = ((sbus[21] >> 5 | sbus[22] << 3) & 0x07FF);
            }
        }
    }
}

int16_t SBUS::getData(uint8_t ch)
{
    return rcChannel[ch];
}

int SBUS::getStickVal(int axis)
{
    switch (axis)
    {
    case 0:
        return map(getData(3), 368, 1680, -255, 255);
        break;
    case 1:
        return map(getData(1), 368, 1680, 255, -255);
        break;
    case 2:
        return map(getData(0), 368, 1680, -255, 255);
        break;
    case 3:
        return map(getData(2), 368, 1680, -255, 255);
        break;
    default:
        return 0;
    }
}

int SBUS::getSwitchVal(int parm)
{
    if (parm == 0)
        return map(getData(4), 144, 1904, 0, 2);
    else if (parm <= 4)
        return map(getData(parm + 5), 144, 1904, 0, 2);
    else
        return 0;
}
