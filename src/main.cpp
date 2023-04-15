#include <Arduino.h>
#include "BMI088_Interface.h"
#include "telemetry_packet.h"

#define BMI088_SCL 19
#define BMI088_SDA 18

// telemetry_packet struct to hold most recently polled sensor data
// malloced in setup() memory 
struct telemetry_packet *telemetry; 

void setup() 
{
    //TODO: remove serial stuff for flight code, eventually replace with radio output
    Serial.begin(9600);
    while(!Serial) {}
    Serial.println("Teensy Serial Output Initialized");

    // malloc the telemetry packet
    telemetry = (struct telemetry_packet *)malloc(sizeof(struct telemetry_packet));

    //initialize the IMU
    BMI088_init(&telemetry->accelX, &telemetry->accelY, &telemetry->accelZ, &telemetry->gyroX, &telemetry->gyroY, &telemetry->gyroZ, &telemetry->temp);
}


void loop()
{
    //TODO: remove serial stuff for flight code, eventually replace with radio output
    Serial.println("main control loop");
    //TODO: add code to read telemetry packet which should be updated by the reader threads
    // for now just loop here reading BMI088 and print the values to main serial
    BMI088_read();
    Serial.print("accelX: ");
    Serial.println(telemetry->accelX);
    Serial.print("accelY: ");
    Serial.println(telemetry->accelY);
    Serial.print("accelZ: ");
    Serial.println(telemetry->accelZ);
    Serial.print("gyroX: ");
    Serial.println(telemetry->gyroX);
    Serial.print("gyroY: ");
    Serial.println(telemetry->gyroY);
    Serial.print("gyroZ: ");
    Serial.println(telemetry->gyroZ);
    Serial.print("temp: ");
    Serial.println(telemetry->temp);
    //TODO: remove the delay for flight code
    delay(1000);
}