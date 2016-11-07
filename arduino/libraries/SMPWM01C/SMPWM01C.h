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

//#define FILTER_WEIGHT 2.0 //set to 1.0 for no filtering
//#define SAMPLE_MS 30000ul

class SMPWM01C {
	
    public:
		
		uint8_t P1_Pin;
		uint8_t P2_Pin;
		
        SMPWM01C();
		
		void begin(uint8_t, uint8_t);
		
		float getPM2();
		
		//float getPM10();
		
    private:
		
		
		//static int statePM10, statePM02;
		
		//static unsigned long startPM10, startPM02; 
		
		//static volatile unsigned long lpoPM10, lpoPM02;
		
		static float ConcentrationPM10, ConcentrationPM02;
		
		unsigned long LPODuration;
		unsigned long SampleStartTime;
		unsigned long SampleDuration;	//duration of sampling in milliseconds
		unsigned long LPOTotal;
		float LPORatio;
       
};

#endif