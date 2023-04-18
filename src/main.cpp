#include <Arduino.h>
#include "GPS_Interface.h"
#include "BMI088_Interface.h"
#include "telemetry_packet.h"
#include "states.h"
#include <TeensyThreads.h>



/*------- GLOBAL VARIABLES -------*/
// telemetry_packet struct to hold most recently polled sensor data
// malloced in setup() memory 
struct telemetry_packet *telemetry; 
// global state variable to be used by all threads as a failsafe in case telemetry packet is not being updated
const volatile mission_state global_state = NAV_CONVERGE;
mission_state * state = (mission_state *) &global_state; // have to cast to non-const pointer to pass to threads

void setup() 
{
    //TODO: remove serial stuff for flight code, eventually replace with radio output
    Serial.begin(9600);
    while(!Serial) {}
    Serial.println("Teensy Serial Output Initialized");



    /*------- INITIALIZE TELEMETRY PACKET -------*/

    // allocate memory for the telemetry packet
    telemetry = (struct telemetry_packet *)malloc(sizeof(struct telemetry_packet));
    // initialize the telemetry packet data
    telemetry->timestamp = 0;
    telemetry->state = NAV_CONVERGE;
    telemetry->accelX = 0;
    telemetry->accelY = 0;
    telemetry->accelZ = 0;
    telemetry->gyroX = 0;
    telemetry->gyroY = 0;
    telemetry->gyroZ = 0;
    telemetry->temperature = 0;
    telemetry->altimeter_data[0] = 0;
    telemetry->altimeter_data[1] = 0;
    telemetry->altimeter_data[2] = 0;
    telemetry->altimeter_data[3] = 0;
    telemetry->latitude = 0;
    telemetry->longitude = 0;
    telemetry->error_code = 0;



    /*------- INITIALIZE SENSORS AND CONNECTIONS-------*/

    //initialize the IMU
    BMI088_Init(&telemetry->accelX, &telemetry->accelY, &telemetry->accelZ, &telemetry->gyroX, &telemetry->gyroY, &telemetry->gyroZ, &telemetry->temperature);
    //initialize the GPS
    GPS_Init(&telemetry->latitude, &telemetry->longitude);


    
    /*------- INITIALIZE THREADS -------*/

    //IMU thread
    threads.addThread(BMI088_Thread_Main, 1);
    //GPS thread
    threads.addThread(GPS_Thread_Main, 2);

    //TODO: add threads for other modules
    
    //Altimeter thread
    // threads.addThread(Altimeter_Thread_Main, 3);
    //Radio thread
    // threads.addThread(Radio_Thread_Main, 4);



    /*------- CHANGE STATE TO PAD_IDLE -------*/
    *state = PAD_IDLE;
    telemetry->state = PAD_IDLE;
    //off to the races!
}


void loop()
{
    //TODO: remove serial stuff for flight code, eventually replace with radio output calls
    Serial.println("main control loop");
    //TODO: add code to read telemetry packet which should be updated by the reader threads
    // for now just loop here reading BMI088 and print the values to main serial
    while(true){ 
        telemetry->timestamp = millis();
        Serial.print("Timestamp: ");
        Serial.println(telemetry->timestamp);
        Serial.print(" Accel X: ");
        Serial.println(telemetry->accelX);
        Serial.print(" Accel Y: ");
        Serial.println(telemetry->accelY);
        Serial.print(" Accel Z: ");
        Serial.println(telemetry->accelZ);
        Serial.print(" Gyro X: ");
        Serial.println(telemetry->gyroX);
        Serial.print(" Gyro Y: ");
        Serial.println(telemetry->gyroY);
        Serial.print(" Gyro Z: ");
        Serial.println(telemetry->gyroZ);
        Serial.print(" Temperature: ");
        Serial.println(telemetry->temperature);
        Serial.print(" GPS Latitude: ");
        Serial.println(telemetry->latitude);
        Serial.print(" GPS Longitude: ");
        Serial.println(telemetry->longitude);
        Serial.print(" State: ");
        Serial.println(telemetry->state);

        delay(500);
    }
}