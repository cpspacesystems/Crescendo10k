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

#ifndef SD_INTERFACE_
#define SD_INTERFACE_
#define LOG_REOPEN_ATTEMPTS 5
#include <Arduino.h>
#include <SD.h>
#include <fstream>
#include "telemetry_packet.h"

#define LOG_FILE_NAME "log.txt"

class SD_Interface 
{
    private:
        /* Pointer to the packet to read from */
        telemetry_packet *packet;
        /* File to log to */
        File logFile;

    public: 
        SD_Interface(telemetry_packet *p) 
        {
            /* Initializes the packet pointer field with the inputted packet pointer. */
            packet = p;

            if(!SD.begin(BUILTIN_SDCARD))
            {
                /* TODO: What other actions should we take if initialization fails? */
                Serial.println("SD initialization failed.");
            }

            Serial.println("SD initialization succeeded.");

            /* Delete the old log file if it exists */
            if(SD.exists(LOG_FILE_NAME))
                SD.remove(LOG_FILE_NAME);

            /* Open the log file in append mode */
            logFile = SD.open(LOG_FILE_NAME, O_WRITE);
            
            /* Check if the file was opened successfully. */
            if(logFile)
            {
                Serial.println("File opened.");
            }
            else
            {
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

        /* TODO: should we address buffer overflow? */

        /* Takes data from the telemetry packet and prints
        it, CSV-formatted, to the file on the SD card */
        void logPacket() 
        {
            /* Print both the timestamp and the state as an integer */
            logFile.print(packet->timestamp);
            logFile.print(", ");
            logFile.print(packet->state);

            /* Print all IMU data points */
            for(int i = 0; i < IMUDATASIZE; i++) 
            {
                logFile.print(", ");
                logFile.print(packet->imu_data[i]);
            }
            
            /* Print all altimeter data points */
            for(int i = 0; i < ALTIMETERDATASIZE; i++) 
            {
                logFile.print(", ");
                logFile.print(packet->altimeter_data[i]);
            }
                

            /* Print all GPS data points */
            for(int i = 0; i < GPSDATASIZE; i++)
            {
                logFile.print(", ");
                logFile.print(packet->gps_data[i]);
            }

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

        /* Closes any open files and saves data */
        void close()
        {
            logFile.close();
            Serial.println("File closed.");
        }

        /* For development. Opens, closes, and dumps contents of the logFile.*/
        void dumpLog()
        {
            File file = SD.open("log.txt");
            
            while(file.available())
                Serial.print((char)(file.read()));

            file.close();
        }
};

#endif // SD_INTERFACE_

