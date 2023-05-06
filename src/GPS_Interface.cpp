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

#define GPS_TX_PIN 21
#define GPS_RX_PIN 20

SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN); 
volatile double *latest_lat;
volatile double *latest_lng;
volatile uint8_t *gps_status_code;
TinyGPSPlus tiny_gps;



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
    ss.begin(9600);
    // wait for serial connection to be established
    while(!ss) {} //TODO: this will timeout 

    // perform status check on GPS module
    while (ss.available() > 0){ //flush the serial buffer
        ss.read();
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
    while(1){ // TODO: change this to a check for mission_state
        gps_status_code = 0; //TODO: add status codes
        
        while (ss.available() > 0){                 
            tiny_gps.encode(ss.read());             //read data from GPS module
            //TODO: add check for valid GPS data
            //TODO: add check for GPS data timeout
            //TODO: add a mutex lock here so data doesn't get corrupted on the other end
            *latest_lat = tiny_gps.location.lat();  //update latest_lat and latest_lng
            *latest_lng = tiny_gps.location.lng();
        }  
    }

}
