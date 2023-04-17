/*  CPP file defining functions for interfacing with BMI088 IMU
    uses the Bolder Flight Systems BMI088 library
    functions declared in BMI088_Interface.h

    first initialize the IMU with BMI088_init()
    create a thread to run BMI088_read() in the background
    BMI088_read() will update the variables on the other side of pointers given in as parameters to BMI088_init()
    main file will then access IMU data and populate the telemetry packet before sending each control cycle
*/

#include <Arduino.h>
#include "BMI088.h"

#define BMI088_SCL 19
#define BMI088_SDA 18

/*
----- Global Variables -----
*/

/* accel object */
Bmi088Accel accel(Wire,0x18);
/* gyro object */
Bmi088Gyro gyro(Wire,0x68);

// IMU data pointers
float *accelX;
float *accelY;
float *accelZ;
float *gyroX;
float *gyroY;
float *gyroZ;
float *temperature;

/*
--Initializer function for BMI088 IMU--
Initializes the IMU and sets up the serial connection for gathering data
*/
void BMI088_init(float *aX, float *aY, float *aZ, float *gX, float *gY, float *gZ, float *t){
    // set the pointers to the global variables
    accelX = aX;
    accelY = aY;
    accelZ = aZ;
    gyroX = gX;
    gyroY = gY;
    gyroZ = gZ;
    temperature = t;

    int status;
    // USB Serial to print data 
    // TODO: Not needed for flight code, remove
    Serial1.begin(115200);
    while(!Serial1) {}
    Serial1.println("Serial1 Initialized");

    // I2C bus for IMU
    Wire.setSDA(BMI088_SDA);
    Wire.setSCL(BMI088_SCL);

    

    Wire.begin();

    /* start the sensors */

    // start the accelerometer
    status = accel.begin();
    // if there's an error, print it and wait forever
    if (status < 0) {
        Serial.println("Accel Initialization Error");
        Serial.println(status);
        while (1) {}
    }
    // start the gyroscope
    status = gyro.begin();
    // if there's an error, print it and wait forever
    if (status < 0) {
        Serial.println("Gyro Initialization Error");
        Serial.println(status);
        while (1) {}
    }

}

/* 
 *   --Read function for BMI088 IMU.--
 *   Reads the IMU data and updates the variables at the pointers
 *   passed in as parameters to BMI088_init()
*/

void BMI088_read(){
    // read the accel
    accel.readSensor();
    // read the gyro
    gyro.readSensor();
    // update global variables for IMU data
    // TODO: add mutex lock here so that the main file can't 
    //       access the data while it's being updated causing weird data mismatches
    *accelX = accel.getAccelX_mss();
    *accelY = accel.getAccelY_mss();
    *accelZ = accel.getAccelZ_mss();
    *gyroX = gyro.getGyroX_rads();
    *gyroY = gyro.getGyroY_rads();
    *gyroZ = gyro.getGyroZ_rads();
    *temperature =  accel.getTemperature_C();
}