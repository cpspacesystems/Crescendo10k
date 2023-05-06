// header file for BMI088_Interface.cpp
// uses the Bolder Flight Systems BMI088 library

#ifndef BMI088_INTERFACE_H
#define BMI088_INTERFACE_H


#include <Arduino.h>
#include "BMI088.h"
#include <TeensyThreads.h>
#include "telemetry_packet.h"

//function declarations
void BMI088_Init( 
    volatile uint8_t *imu_status_code,
    volatile float *aX, volatile float *aY, volatile float *aZ,
    volatile float *gX, volatile float *gY, volatile float *gZ, 
    volatile float *t);
void BMI088_Thread_Main();

#endif


