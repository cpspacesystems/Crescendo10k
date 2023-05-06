/*
 * cpp file containing functions run by main during each mission state
 * each function will perform necessary tasks or set flags for other threads to perform tasks within each state
 * each function will update the mission state variable in the telemetry packet and change the function pointer.
*/

#include <Arduino.h>
#include <TeensyThreads.h>
#include "telemetry_packet.h"
#include "GPS_Interface.h"
#include "BMI088_Interface.h"
// #include "Radio_Interface.h"
// #include "BMP390_Interface.h"
// #include "SD_Interface.h"

void state_nav_converge(){
    
}
void state_pad_idle(){

}
void state_ascent(){

}
void state_apogee(){

}
void state_descent(){

}
void state_landed(){

}
void state_recovery(){

}
