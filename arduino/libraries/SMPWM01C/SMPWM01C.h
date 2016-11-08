// Amphenol Advanced Sensors SMPWM01C
// 
// Pin1 - GND
// Pin2 - OUTPUT P2 particles > 2um
// Pin3 - 5V
// Pin4 - OUTPUT P1 particles ~ 1um
// Pin5 - NC
//

#ifndef SMPWM01C_h
#define SMPWM01C_h
#include <Arduino.h>

#define FILTER_WEIGHT 2.0 //set to 1.0 for no filtering

class SMPWM01C {
	
    public:
		
		uint8_t PM2_Pin;
		uint8_t PM10_Pin;
		
        SMPWM01C();
		
		void begin(uint8_t, uint8_t);
		
		float getPM2();
		float getPM10();
		
    private:
		
		float PM2Concentration;
		float PM10Concentration;
		
		float LPODuration;
		float SampleStartTime;
		float SampleDuration;	//duration of sampling in milliseconds
		float LPOTotal;
		float LPORatio;
       
};

#endif