/*
    * Telemetry Packet
    * 
    * This file contains the class definition for the Telemetry Packet class.
    * This class is used to create a packet of data to be sent to the ground.
    * Data included in the packet is the following:
    * - a timestamp
    * - current state
    * - most recent IMU poll
    * - most recent altimeter poll
    * - most recent GPS poll
    * Author: Cameron McClure-Coleman
*/




#ifndef TELEMETRY_PACKET_H_
#define TELEMETRY_PACKET_H_

#define     NO_ERROR 0
#define     UNEXPECTED_ERROR 1

     // state error codes
#define     NAV_CONVERGE_TIMEOUT 5

    // initialization error codes
#define     GPS_INITIALIZATION_TIMEOUT 20
#define     IMU_INITIALIZATION_TIMEOUT 21
#define     IMU_ACCEL_INITIALIZATION_ERROR 22
#define     IMU_GYRO_INITIALIZATION_ERROR 23
#define     ALTIMETER_INITIALIZATION_TIMEOUT 24
#define     RADIO_INITIALIZATION_TIMEOUT 25

    // timeout error codes
#define     GPS_TIMEOUT 40
#define     IMU_TIMEOUT 41
#define     ALTIMETER_TIMEOUT 42
#define     RADIO_TIMEOUT 43

    // data error codes
#define     GPS_DATA_ERROR 60
#define     IMU_DATA_ERROR 61
#define     ALTIMETER_DATA_ERROR 62
#define     RADIO_DATA_ERROR 63

#include <Arduino.h>
#include "states.h"

#define IMUDATASIZE 6
#define ALTIMETERDATASIZE 4
#define GPSDATASIZE 4
// Telemetry Packet Struct Definition 
struct telemetry_packet{
<<<<<<< HEAD
    uint32_t timestamp;
    mission_state state;
    uint8_t imu_data[IMUDATASIZE];
    uint8_t altimeter_data[ALTIMETERDATASIZE];
    uint8_t gps_data[GPSDATASIZE];
=======

    volatile uint32_t timestamp;
    volatile mission_state mission_state;

    volatile uint8_t imu_status;
    volatile float imu_accelX; 
    volatile float imu_accelY; 
    volatile float imu_accelZ; 
    volatile float imu_gyroX; 
    volatile float imu_gyroY; 
    volatile float imu_gyroZ; 
    volatile float imu_temperature;

    volatile uint8_t altimeter_status;
    uint8_t altimeter_data[4]; 

    volatile uint8_t gps_status;
    volatile double gps_latitude;
    volatile double gps_longitude;
    
>>>>>>> main
};




#endif // TELEMETRY_PACKET_H_