#include <Arduino.h>
#include "GPS_Interface.h"
#include "BMI088_Interface.h"
#include "SD_Interface.h"
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
    //TODO: BIG TODO, put all the module initialization into nav converge state function instead of here because nav converge is never transmitted currently.
    // also initialize radio first so that it can be used to transmit errors if other modules fail to initialize
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
    telemetry->altimeter_data[0] = 0;
    telemetry->altimeter_data[1] = 0;
    telemetry->altimeter_data[2] = 0;
    telemetry->altimeter_data[3] = 0;
    // GPS data
    telemetry->gps_latitude = 0;
    telemetry->gps_longitude = 0;
    telemetry->gps_status = 0;




    /*------- INITIALIZE SENSORS AND CONNECTIONS-------*/

    //initialize the IMU
    BMI088_Init(
        &telemetry->imu_status, 
        &telemetry->imu_accelX, &telemetry->imu_accelY, &telemetry->imu_accelZ, 
        &telemetry->imu_gyroX, &telemetry->imu_gyroY, &telemetry->imu_gyroZ, 
        &telemetry->imu_temperature);
    //initialize the GPS
    GPS_Init(&telemetry->gps_status, &telemetry->gps_latitude, &telemetry->gps_longitude);


    
    /*------- INITIALIZE THREADS -------*/

    //IMU thread
    threads.addThread(BMI088_Thread_Main, 1);
    //GPS thread
    threads.addThread(GPS_Thread_Main, 2);

    //TODO: add threads for other modules
    
    //Altimeter thread
    // threads.addThread(Altimeter_Thread_Main, 3);
    //Radio thread
    // threads.addThread(Radio_Thread_Main, 4);

    /*------- CHANGE STATE TO PAD_IDLE -------*/
    *state = PAD_IDLE;
    telemetry->mission_state = PAD_IDLE;
    //off to the races!
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