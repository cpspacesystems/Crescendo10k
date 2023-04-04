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

#include <Arduino.h>
#include "states.h"

// Telemetry Packet Struct Definition 
struct telemetry_packet{
    uint32_t timestamp;
    mission_state state;
    uint8_t imu_data[6];
    uint8_t altimeter_data[4];
    uint8_t gps_data[4];
};

#endif // TELEMETRY_PACKET_H_