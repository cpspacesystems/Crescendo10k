#include <Arduino.h>
#include "GPS_Interface.cpp"

GroveGPS gps;

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(22, INPUT);
    Serial.begin(9600);

    gps = GroveGPS();
    
}


void loop()
{
    POS pos = gps.get_pos();
    Serial.printf("Lat: %f, Lng: %f\n", pos.lat, pos.lng);
}