/* Header file for the GPS_Interface.cpp file
 * Uses the TinyGPS++ library
 */

#ifndef GPS_INTERFACE_H_
#define GPS_INTERFACE_H_

#include <Arduino.h>
#include "TinyGPS++.h"
#include <SoftwareSerial.h>
#include <TeensyThreads.h>

void GPS_Init(volatile uint8_t *gps_status_code, volatile double *lattitude, volatile double *longitude);
void GPS_Thread_Main();
void packetize_gps_data();

#endif // GPS_INTERFACE_H_