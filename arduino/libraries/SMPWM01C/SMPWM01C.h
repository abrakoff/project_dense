// Amphenol Advanced Sensors SMPWM01C
// 
// Pin1 - GND
// Pin2 - OUTPUT P2 particles > 2um (PM10)
// Pin3 - 5V
// Pin4 - OUTPUT P1 particles ~ 1um	(PM2.5)
// Pin5 - NC
//

#ifndef SMPWM01C_h
#define SMPWM01C_h
#include <Arduino.h>

//#define FILTER_WEIGHT 2.0

class SMPWM01C {
	
    public:
		
		//Pins for PM2.5 and PM10
		uint8_t PM2_Pin;
		uint8_t PM10_Pin;
		
        SMPWM01C();
		
		//Function for initializing SMPWM01C (assign input pins)
		void begin(uint8_t, uint8_t);
		
		//Functions to retrive PM2.5 and PM10 concentrations (blocking)
		float getPM2();
		float getPM10();
		
    private:
		
		float PM2Concentration;
		float PM10Concentration;
		
		float LPODuration;
		float SampleStartTime;
		float SampleDuration;	
		float LPOTotal;
		float LPORatio;
       
};

#endif