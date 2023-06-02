/*  CPP file containing functions for interfaceing with the GPS module
 *  uses the TinyGPS++ library
 *  functions declared in GPS_Interface.h
 * 
 *  first initialize the GPS module with GPS_Init()
 *  create a thread to run GPS_Thread_Main() in the background
 *  GPS_Thread_Main() will update the variables on the other side of pointers given in as parameters to GPS_Init()
 *  main file should then access GPS data and populate the telemetry packet before sending each control cycle
 */ 

//q: why am I getting multiple declaration errors for this file when I compile?
//a:    

#include <Arduino.h>
#include "TinyGPS++.h"
#include <SoftwareSerial.h>
#include <TeensyThreads.h>
#include "telemetry_packet.h"

#define GPS_TX_PIN 21
#define GPS_RX_PIN 20

SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN); 
volatile double *latest_lat;
volatile double *latest_lng;
volatile uint8_t *gps_status_code;
TinyGPSPlus tiny_gps;
static const uint32_t GPSBaud = 4800;


/* -------- GPS INITIALIZATION FUNCTION --------
This function is called by main.cpp to initialize the GPS module connection and variables
*/

void GPS_Init(volatile uint8_t *gps_status, volatile double *lattitude, volatile double *longitude){
    // store pointers to latest telemetry packet variables
    latest_lat = lattitude;
    latest_lng = longitude;
    gps_status_code = gps_status;
    tiny_gps = TinyGPSPlus(); // initialize TinyGPS++ object

    // set GPIO pins for SoftwareSerial connection to GPS module
    // pinMode(GPS_TX_PIN, OUTPUT); //GPS TX
    // pinMode(GPS_RX_PIN, INPUT);  //GPS RX

    
    // begin SoftwareSerial connection to GPS module
    ss.begin(GPSBaud);
    // wait for serial connection to be established
    uint16_t gps_init_timeout = 1000;
    while(!ss || gps_init_timeout > 0){
        *gps_status_code = GPS_SERIAL_CONNECTION_ERROR;
        gps_init_timeout--;
    }
    if(gps_init_timeout == 0){
        *gps_status_code = GPS_INITIALIZATION_TIMEOUT;
    } else
    {
        *gps_status_code = NO_ERROR;
    }
    
}

void packetize_gps_data(){
  // check the GPS module for new data that is valid
  if (tiny_gps.location.isValid())
  {
    *latest_lat = tiny_gps.location.lat();
    *latest_lng = tiny_gps.location.lng();
    *gps_status_code = NO_ERROR;
  }
  else
  {
    *gps_status_code = GPS_DATA_ERROR;
  }
}

/*  -------- GPS THREAD FUNCTION --------
 *  
 *  This function is the main function for the GPS thread
 *  Main.cpp will call threads.addThread() on this function to start the thread
 *  thread should update latest_lat and latest_lng
 *  thread does not need to check mission state like other modules
 *  GPS thread will always run regardless of mission state becasue it is used for recovery (also Radio TX)
*/
void GPS_Thread_Main(){

    /*----- MAIN CONTROL LOOP ----*/
        //TODO: add check for mission state
    {
  // This sketch displays information every time a new sentence is correctly encoded.
    while (ss.available() > 0){
        if (tiny_gps.encode(ss.read())){}
            packetize_gps_data();
        }
    }

  if (millis() > 5000 && tiny_gps.charsProcessed() < 10)
  {
    *gps_status_code = GPS_INITIALIZATION_ERROR;
  }

}



