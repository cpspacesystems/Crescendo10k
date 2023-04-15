#include <Arduino.h>
#include "GPS_Interface.cpp"

GroveGPS gps;

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(21, OUTPUT); //GPS TX
    pinMode(22, INPUT);  //GPS RX
    // Serial.begin(9600);

    gps = GroveGPS();
    gps.update_pos();
}


void loop()
{
    // POS pos = gps.get_pos();
    // Serial.printf("Lat: %f, Lng: %f\n", pos.lat, pos.lng);
}