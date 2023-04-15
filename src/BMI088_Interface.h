// header file for BMI088_Interface.cpp
// uses the Bolder Flight Systems BMI088 library

#ifndef BMI088_INTERFACE_H
#define BMI088_INTERFACE_H
#include <Arduino.h>
#include "BMI088.h"

// /* accel object */
// Bmi088Accel accel;
// /* gyro object */
// Bmi088Gyro gyro;

//function declarations
void BMI088_init(float *aX, float *aY, float *aZ, float *gX, float *gY, float *gZ, float *t);
void BMI088_read();

#endif


