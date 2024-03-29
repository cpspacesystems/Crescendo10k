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
*/




#ifndef TELEMETRY_PACKET_H_
#define TELEMETRY_PACKET_H_

#define     NO_ERROR 0
#define     UNEXPECTED_ERROR 1

     // state error codes
#define     NAV_CONVERGE_TIMEOUT 5

    // initialization error codes
#define     GPS_INITIALIZATION_TIMEOUT 20
#define     GPS_INITIALIZATION_ERROR 21
#define     IMU_INITIALIZATION_TIMEOUT 22
#define     IMU_ACCEL_INITIALIZATION_ERROR 23
#define     IMU_GYRO_INITIALIZATION_ERROR 24
#define     ALTIMETER_INITIALIZATION_TIMEOUT 25
#define     RADIO_INITIALIZATION_TIMEOUT 26

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

    // board to module connection error codes
#define     GPS_SERIAL_CONNECTION_ERROR 80


#include <Arduino.h>
#include "states.h"
// Telemetry Packet Struct Definition 
struct telemetry_packet{

    volatile uint32_t timestamp;
    volatile Mission_State mission_state;
    volatile int radio_status;
    volatile uint8_t imu_status;
    volatile float imu_accelX; 
    volatile float imu_accelY; 
    volatile float imu_accelZ; 
    volatile float imu_gyroX; 
    volatile float imu_gyroY; 
    volatile float imu_gyroZ; 
    volatile float imu_temperature;
    volatile uint8_t altimeter_status;
    volatile double altimeter_temperature;
    volatile double altimeter_pressure;
    volatile double altimeter_altitude;
    volatile uint8_t gps_status;
    volatile double gps_latitude;
    volatile double gps_longitude;
    volatile double gps_altitude;
};

#endif // TELEMETRY_PACKET_H_