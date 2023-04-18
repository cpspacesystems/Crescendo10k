/*  CPP file defining functions for interfacing with BMI088 IMU
 *  uses the Bolder Flight Systems BMI088 library
 *  functions declared in BMI088_Interface.h
 *  
 *  first initialize the IMU with BMI088_Init()
 *  create a thread to run BMI088_Thread_Main() in the background
 *  BMI088_Thread_Main()) will update the variables on the other side of pointers given in as parameters to BMI088_Init()
 *  main file should then access IMU data and populate the telemetry packet before sending each control cycle
*/

#include <Arduino.h>
#include "BMI088.h"
#include <TeensyThreads.h>

#define BMI088_SCL 19
#define BMI088_SDA 18
// these are the I2C addresses for the BMI088 IMU determined by what the SDO pins are connected to on the board
// SDO1 and SDO2 are both connected to ground on the board. these are the addresses for that configuration:
#define BMI088_SDO1 0x18
#define BMI088_SDO2 0x68


/*
----- Global Variables -----
*/

/* accel object */
Bmi088Accel accel(Wire, BMI088_SDO1 );
/* gyro object */
Bmi088Gyro gyro(Wire, BMI088_SDO2);


// IMU data pointers
float *accelX;
float *accelY;
float *accelZ;
float *gyroX;
float *gyroY;
float *gyroZ;
float *temperature;

/*
 *  -------Initializer function for BMI088 IMU--------
 *  Initializes the IMU and sets up the serial connection for gathering data
 */
void BMI088_Init(float *aX, float *aY, float *aZ, float *gX, float *gY, float *gZ, float *t){
    // set the pointers to the global variables
    accelX = aX;
    accelY = aY;
    accelZ = aZ;
    gyroX = gX;
    gyroY = gY;
    gyroZ = gZ;
    temperature = t;

    int status;
    Wire.setSCL(BMI088_SCL);
    Wire.setSDA(BMI088_SDA);
    Wire.begin();

    /* start the sensors */

    // start the accelerometer
    status = accel.begin();
    // if there's an error, print it and set the errror flag
    if (status < 0) {
        Serial.println("Accel Initialization Error");
        Serial.println(status);
    }
    // start the gyroscope
    status = gyro.begin();
    // if there's an error, print it and set the error flag
    if (status < 0) {
        Serial.println("Gyro Initialization Error");
        Serial.println(status);
    }

}

/* 
 *  ------- IMU THREAD MAIN FUNCTION -------
 *  Reads the IMU data and updates the variables at the telemetry packet components at the pointers
 *  passed in as parameters to BMI088_init()
*/

void BMI088_Thread_Main(){
    // while loop to read the IMU data
    // TODO: check the mission state to see if the thread needs to end. if so, break out of loop and end thread
    while (true){
        // read the accel
        accel.readSensor();
        // read the gyro
        gyro.readSensor();
        // update global variables for IMU data
        // TODO: add mutex lock on here so that main.cpp can't access while thread is updating causing data mismatches
        *accelX = accel.getAccelX_mss();
        *accelY = accel.getAccelY_mss();
        *accelZ = accel.getAccelZ_mss();
        *gyroX = gyro.getGyroX_rads();
        *gyroY = gyro.getGyroY_rads();
        *gyroZ = gyro.getGyroZ_rads();
        *temperature =  accel.getTemperature_C();
    }
}