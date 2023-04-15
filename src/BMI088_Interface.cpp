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
float *temp;
//Initializer function for BMI088 IMU
//initializes the IMU and sets up the serial connection for gathering data
void BMI088_init(float *aX, float *aY, float *aZ, float *gX, float *gY, float *gZ, float *t){
    // set the pointers to the global variables
    accelX = aX;
    accelY = aY;
    accelZ = aZ;
    gyroX = gX;
    gyroY = gY;
    gyroZ = gZ;
    temp = t;

    int status;
    // USB Serial to print data 
    // TODO: Not needed for flight code, remove
    Serial.begin(115200);
    while(!Serial) {}
    /* start the sensors */
    status = accel.begin();
    if (status < 0) {
        Serial.println("Accel Initialization Error");
        Serial.println(status);
        while (1) {}
    }
    status = gyro.begin();
    if (status < 0) {
        Serial.println("Gyro Initialization Error");
        Serial.println(status);
        while (1) {}
    }

}

//Read function for BMI088 IMU
//reads the IMU data and updates the global variables for the IMU data in the main file
void BMI088_read(){
    /* read the accel */
    accel.readSensor();
    /* read the gyro */
    gyro.readSensor();
    /* print the data */
    // TODO: instead of printing, update global variables for IMU data
    Serial.print(accel.getAccelX_mss());
    Serial.print("\t");
    Serial.print(accel.getAccelY_mss());
    Serial.print("\t");
    Serial.print(accel.getAccelZ_mss());
    Serial.print("\t");
    Serial.print(gyro.getGyroX_rads());
    Serial.print("\t");
    Serial.print(gyro.getGyroY_rads());
    Serial.print("\t");
    Serial.print(gyro.getGyroZ_rads());
    Serial.print("\t");
    Serial.print(accel.getTemperature_C());
    Serial.print("\n");
    /* delay to help with printing */
    delay(20);
}