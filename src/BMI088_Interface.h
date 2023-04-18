// header file for BMI088_Interface.cpp
// uses the Bolder Flight Systems BMI088 library

#ifndef BMI088_INTERFACE_H
#define BMI088_INTERFACE_H
#include <Arduino.h>
#include "BMI088.h"

//function declarations
void BMI088_Init(float *aX, float *aY, float *aZ, float *gX, float *gY, float *gZ, float *t);
void BMI088_Thread_Main();

#endif


