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
<<<<<<< HEAD
    //TODO: remove serial stuff for flight code, eventually replace with radio output
    Serial.begin(9600);
    while(!Serial) {}
    Serial.println("Teensy Serial Output Initialized");

    // malloc the telemetry packet
    telemetry = (struct telemetry_packet *)malloc(sizeof(struct telemetry_packet));

    //initialize the IMU
    BMI088_init(&telemetry->accelX, &telemetry->accelY, &telemetry->accelZ, &telemetry->gyroX, &telemetry->gyroY, &telemetry->gyroZ, &telemetry->temperature);
=======
    pinMode(LED_BUILTIN, OUTPUT);
>>>>>>> 0f7b92e (added get_pos method)
}


void loop()
{
<<<<<<< HEAD
    //TODO: remove serial stuff for flight code, eventually replace with radio output calls
    Serial.println("main control loop");
    //TODO: add code to read telemetry packet which should be updated by the reader threads
    // for now just loop here reading BMI088 and print the values to main serial
    while(true){ 
        BMI088_read();
    }
=======
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
>>>>>>> 0f7b92e (added get_pos method)
}