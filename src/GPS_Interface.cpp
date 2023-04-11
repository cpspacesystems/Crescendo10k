#include <Arduino.h>
#include "TinyGPS++.h"

union POS {double lat; double lng;}; //position union

class GroveGPS{

    public:
    POS latest_pos;
    TinyGPSPlus gps;
    
    GroveGPS(){
        latest_pos.lat = 0;
        latest_pos.lng = 0;
        gps = TinyGPSPlus();
    }
    
    


    POS get_pos(){

        GroveGPS::latest_pos.lat = gps.location.lat();
        GroveGPS::latest_pos.lng = gps.location.lng();

        return latest_pos;
    }

    double get_lat(){

        GroveGPS::latest_pos.lat = gps.location.lat();

        return latest_pos.lat;
    }

    double get_lng(){

        GroveGPS::latest_pos.lng = gps.location.lng();

        return latest_pos.lng;
    }

    void update_pos(){
            while (Serial1.available() > 0) {
                gps.encode(Serial1.read());
            }
    }
};
