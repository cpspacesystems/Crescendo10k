#include <Arduino.h>
#include "SD_Interface.cpp"
#include "states.h"
#include "SD_Interface.h"
#include "GPS_Interface.h"
#include "BMI088_Interface.h"
#include "telemetry_packet.h"
#include "states.h"
#include <TeensyThreads.h>


/*------- GLOBAL VARIABLES -------*/
// telemetry_packet struct to hold most recently polled sensor data
// malloced in setup() memory 
struct telemetry_packet *telemetry; 
// global state variable to be used by all threads as a failsafe in case telemetry packet is not being updated
const volatile mission_state global_state = NAV_CONVERGE;
mission_state * state = (mission_state *) &global_state; // have to cast to non-const pointer to pass to threads

void setup() 
{
    //TODO: remove serial stuff for flight code, eventually replace with radio output
    Serial.begin(9600);
    while(!Serial) {}
    Serial.println("Teensy Serial Output Initialized");



    /*------- INITIALIZE TELEMETRY PACKET -------*/

    // allocate memory for the telemetry packet
    telemetry = (struct telemetry_packet *)malloc(sizeof(struct telemetry_packet));
    // initialize the telemetry packet data
    telemetry->timestamp = 0;
    telemetry->mission_state = NAV_CONVERGE;
    // imu data
    telemetry->imu_status = 0;
    telemetry->imu_accelX = 0;
    telemetry->imu_accelY = 0;
    telemetry->imu_accelZ = 0;
    telemetry->imu_gyroX = 0;
    telemetry->imu_gyroY = 0;
    telemetry->imu_gyroZ = 0;
    telemetry->imu_temperature = 0;
    // altimeter data
    telemetry->altimeter_status = 0;
    telemetry->altimeter_temperature = 0;
    telemetry->altimeter_pressure = 0;
    telemetry->altimeter_altitude = 0;
    // GPS data
    telemetry->gps_status = 0;
    telemetry->gps_latitude = 0;
    telemetry->gps_longitude = 0;
    telemetry->gps_altitude = 0;

    
    


    /*------- CHANGE STATE TO NAV_CONVERGE -------*/
    *state = NAV_CONVERGE;
    telemetry->mission_state = NAV_CONVERGE;
    // off to the races!
    // nav converge handle making sure all modules are initialized before moving on to pad_idle
}

void loop()
{
    //TODO: remove serial stuff for flight code. This is just for testing
    Serial.println("main control loop");

    while(true){ 
        telemetry->timestamp = millis();
        Serial.print("Timestamp: ");
        Serial.println(telemetry->timestamp);
        Serial.print(" Accel X: ");
        Serial.println(telemetry->imu_accelX);
        Serial.print(" Accel Y: ");
        Serial.println(telemetry->imu_accelY);
        Serial.print(" Accel Z: ");
        Serial.println(telemetry->imu_accelZ);
        Serial.print(" Gyro X: ");
        Serial.println(telemetry->imu_gyroX);
        Serial.print(" Gyro Y: ");
        Serial.println(telemetry->imu_gyroY);
        Serial.print(" Gyro Z: ");
        Serial.println(telemetry->imu_gyroZ);
        Serial.print(" Temperature: ");
        Serial.println(telemetry->imu_temperature);
        Serial.print(" GPS Latitude: ");
        Serial.println(telemetry->gps_latitude);
        Serial.print(" GPS Longitude: ");
        Serial.println(telemetry->gps_longitude);
        Serial.print(" State: ");
        Serial.println(telemetry->mission_state);
        Serial.print(" GPS Status: ");
        Serial.println(telemetry->gps_status);
        Serial.println("IMU Status: ");
        Serial.println(telemetry->imu_status);
        Serial.println("Altimeter Status: ");
        Serial.println(telemetry->altimeter_status);



        delay(50); // remove this for flight code and run at max speed allowable by sensors
    }
}