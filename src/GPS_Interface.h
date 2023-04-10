#include <Arduino.h>
#include "TinyGPS++.h"

union POS {double lat; double lng;}; //position union

class GroveGPS{

    public:

    TinyGPSPlus gps;
    POS pos;
    

    POS get_pos(){

        GroveGPS::pos.lat = gps.location.lat();
        GroveGPS::pos.lng = gps.location.lng();

        return pos;
    }

};


