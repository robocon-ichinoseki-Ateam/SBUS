#include "SBUS.hpp"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(A4, A5);

SBUS propo;

#define STX 255

void setup()
{
    propo.init();
    mySerial.begin(57600);

    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop()
{
    propo.readData();

    unsigned char packet[9] = {0}; // 送信データ（パケット）
    int sum = 0;
    int i = 0;

    for (int i = 0; i < 4; i++)
    {
        if (abs(propo.getStickVal(i)) > 50)
        {
            digitalWrite(6, HIGH);
            break;
        }
        digitalWrite(6, LOW);
    }

    packet[0] = STX; // スタートバイト

    // failsafe
    if (propo.isFailSafe())
    {
        packet[1] = 1;
        digitalWrite(7, HIGH);
    }
    else
    {
        packet[1] = 0;
        digitalWrite(7, LOW);
    }

    // スティックの符号と絶対値をそれぞれのパケットに代入
    for (i = 0; i <= 3; i++)
    {
        if (propo.getStickVal(i) < 0)
            packet[2] += (1 << i);

        // データが255だとSTXと区別が付かなくなるのでガードする
        if (abs(propo.getStickVal(i)) != 255)
            packet[i + 3] = abs(propo.getStickVal(i));
        else
            packet[i + 3] = 254;
    }

    // SW
    packet[2] += (propo.getSwitchVal(4) << 4);
    packet[7] += (propo.getSwitchVal(3) << 6) +
                 (propo.getSwitchVal(2) << 4) +
                 (propo.getSwitchVal(1) << 2) +
                 (propo.getSwitchVal(0));

    // チェックサムの計算
    for (i = 2; i <= 7; i++)
        sum ^= packet[i];

    // チェックサムが255にならないようにする
    if (sum != 255)
        packet[8] = sum;
    else
        packet[8] = 254;

    // パケットを順番に送信
    for (i = 0; i <= 8; i++)
    {
        mySerial.write(packet[i]);

        // mySerial.write(i);
        delayMicroseconds(50);
    }

    delay(50);
}
