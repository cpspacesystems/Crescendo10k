/*
    * SD Card Interface
    * 
    * This file contains the definition for the sd_log class,
    * which provides some functions for reading from a 
    * telemetry_packet instance and writing to a file with name
    * #defined by LOG_FILE_NAME. The data written to this
    * file is CSV-formatted.
    * 
    * The class is initialized with a pointer to the telemetry
    * packet spot to read from. It uses the built-in Teensy 
    * SD card slot. It is assumed that any data that is saved
    * to this SD card or sent back over radio is placed into 
    * the memory block that sd_log was initialized with.
    * 
    * Author: Spandan Suthar
*/
#ifndef SD_INTERFACE_CPP
#define SD_INTERFACE_CPP

#define LOG_REOPEN_ATTEMPTS 5
#include <Arduino.h>
#include <SD.h>
#include <fstream>
#include "telemetry_packet.h"

#define LOG_FILE_NAME "log.csv"


/* Pointer to the packet to read from */
telemetry_packet *packet;
/* File to log to */
File logFile;


        /* TODO: should we address buffer overflow? */

        /* Takes data from the telemetry packet and prints
        it, CSV-formatted, to the file on the SD card */
void logPacket() 
{
    /* Print both the timestamp and the state as an integer */
    logFile.print(packet->timestamp);
    logFile.print(", ");
    logFile.print(packet->mission_state);
    logFile.print(", ");

    /* Print radio status */
    logFile.print(packet->radio_status);
    logFile.print(", ");

    /* Print all IMU data points */
    logFile.print(packet->imu_status);
    logFile.print(", ");
    logFile.print(packet->imu_accelX);
    logFile.print(", ");
    logFile.print(packet->imu_accelY);
    logFile.print(", ");
    logFile.print(packet->imu_accelZ);
    logFile.print(", ");
    logFile.print(packet->imu_gyroX);
    logFile.print(", ");
    logFile.print(packet->imu_gyroY);
    logFile.print(", ");
    logFile.print(packet->imu_gyroZ);
    logFile.print(", ");
    logFile.print(packet->imu_temperature);
    logFile.print(", ");
    
    /* Print all altimeter data points */
    logFile.print(packet->altimeter_status);
    logFile.print(", ");
    logFile.print(packet->altimeter_temperature);
    logFile.print(", ");
    logFile.print(packet->altimeter_pressure);
    logFile.print(", ");
    logFile.print(packet->altimeter_altitude);
    logFile.print(", ");
    
    /* Print all GPS data points */
    logFile.print(packet->gps_status);
    logFile.print(", ");
    logFile.print(packet->gps_latitude);
    logFile.print(", ");
    logFile.print(packet->gps_longitude);
    logFile.print(", ");
    logFile.print(packet->gps_altitude);
    logFile.print(", ");

    /* Print a newline */
    logFile.println();
    
}


/* Attempt to re-open the log file a LOG_REOPEN_ATTEMPTS
times. */
bool logOpenRetry(int n)
{
    for(int i = 0; i < n; i++)
    {

        /* Open the log file in append mode */
        logFile = SD.open(LOG_FILE_NAME, O_WRITE);
        Serial.println("File opened.");

        /* Check if the file was opened successfully. */
        if(logFile)
            return true;

        /* If not, state there was an error and continue retrying*/
        Serial.print("Error opening ");
        Serial.print(LOG_FILE_NAME);
        Serial.print(".\n");
    }

    return false;
}


void SD_Init(telemetry_packet *p){
    /* TODO: change this to initialize a reader from flash memory 
                the SD card is only written to after touchdown */
    packet = p; // Initialize pointer to telemetry packet

    /*---Initialize Connection to SD Card---*/

    
    if(!SD.begin(BUILTIN_SDCARD)){
        /* TODO: update sd status in telemetry packet and let it transmit 
        also, remove print statements*/
        Serial.println("SD initialization failed.");
    }

    /*---Initialize file pointer for log file on SD card---*/

    /* Open the log file in append mode */
    logFile = SD.open(LOG_FILE_NAME, O_WRITE);
    /* Check if the file was opened successfully. */
    if(logFile) {
        Serial.println("File opened.");
    } else {
        /* If not, state there was an error... */
        Serial.print("Error opening ");
        Serial.print(LOG_FILE_NAME);
        Serial.println(".");
        Serial.println("Trying again.");

        /* ...and retry opening the file a #defined number of times.*/
        if(logOpenRetry(LOG_REOPEN_ATTEMPTS))
            Serial.println("File opened.");
        else
            Serial.println("Opening log file failed; giving up.");
    }
}


void SD_Thread_Main(){

}



/* Closes any open files and saves data */
void close()
{
    logFile.close();
    Serial.println("File closed.");
}


/* For development. Opens, closes, and dumps contents of the logFile.*/
void dumpLog()
{
    File file = SD.open(LOG_FILE_NAME);
    
    while(file.available())
        Serial.print((char)(file.read()));

    file.close();
}


#endif