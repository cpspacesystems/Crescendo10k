#include <Arduino.h>
#include "SD_Interface.cpp"
#include "states.h"

static telemetry_packet packet = {
    100, 
    PAD_IDLE, 
    {0, 1, 2, 3, 4, 5},
    {6, 7, 8, 9},
    {10, 11, 12, 13}
};

static SD_Interface *sDLog;

void setup() 
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);

    sDLog = new SD_Interface(&packet);

    sDLog->logPacket();

    sDLog->close();
}


void loop()
{
    digitalWrite(2, LOW);
    delay(1000);
    digitalWrite(2, HIGH);
    delay(1000);
}