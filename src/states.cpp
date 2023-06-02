/*
 * cpp file containing functions run by main during each mission state
 * each function will perform necessary tasks or set flags for other threads to perform tasks within each state
 * each function will update the mission state variable in the telemetry packet and change the function pointer.
*/

#include <Arduino.h>
#include <TeensyThreads.h>
#include "telemetry_packet.h"
#include "GPS_Interface.h"
#include "BMI088_Interface.h"
// #include "Radio_Interface.h"
// #include "BMP390_Interface.h"
// #include "SD_Interface.h"

struct telemetry_packet *telemetry;
uint8_t *state;

void state_nav_converge(struct telemetry_packet *telemetry_pointer, uint8_t *state_pointer){
    /*------- INITIALIZE TELEMETRY POINTERS-------*/

    //initialize the telemetry packet pointer
    telemetry = telemetry_pointer;
    //initialize the state variable pointer
    state = state_pointer;

    /*------- INITIALIZE SENSORS AND CONNECTIONS-------*/

    //initialize the IMU
    BMI088_Init(
        &telemetry->imu_status, 
        &telemetry->imu_accelX, &telemetry->imu_accelY, &telemetry->imu_accelZ, 
        &telemetry->imu_gyroX, &telemetry->imu_gyroY, &telemetry->imu_gyroZ, 
        &telemetry->imu_temperature);

    //initialize the GPS
    //TODO: update GPS init function to take in pointer to status code
    GPS_Init(&telemetry->gps_status, &telemetry->gps_latitude, &telemetry->gps_longitude);

    /*------- INITIALIZE THREADS -------*/

    //IMU thread
    threads.addThread(BMI088_Thread_Main, 1);
    //GPS thread
    threads.addThread(GPS_Thread_Main, 2);
    
    //Altimeter thread
    // threads.addThread(Altimeter_Thread_Main, 3);
    //Radio thread
    // threads.addThread(RFD_Thread_Main, 4);
    //SD thread
    // threads.addThread(SD_Thread_Main, 5);

    /*------- CHANGE STATE TO PAD IDLE -------*/
    *state = PAD_IDLE;
    telemetry->mission_state = PAD_IDLE;
}

void state_pad_idle(){

}
void state_ascent(){

}
void state_apogee(){

}
void state_descent(){

}
void state_landed(){

}
void state_recovery(){

}
