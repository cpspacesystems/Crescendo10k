/*Header file for SD_Interface.cpp*/
#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <Arduino.h>
#include <SD.h>
#include <fstream>
#include "telemetry_packet.h"

#define LOG_FILE_NAME "log.csv"

/* publicly accessible functioins */
void SD_Init(telemetry_packet *p);
void SD_Thread_Main();
bool logOpenRetry(int attempts);
void close();
void dumpLog();
void logPacket();

#endif