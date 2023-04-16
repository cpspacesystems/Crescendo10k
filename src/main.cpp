#include <Arduino.h>
#include "SD_Interface.cpp"
#include "states.h"

static telemetry_packet packet = {
    0, 
    (mission_state)6, 
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static SD_Interface *sDLog;

void setup() 
{

}

void loop()
{

}