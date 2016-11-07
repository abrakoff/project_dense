#include "SMPWM01C.h"

SMPWM01C::SMPWM01C() {}

float SMPWM01C::ConcentrationPM02;
float SMPWM01C::ConcentrationPM10;

unsigned long LPODuration;
unsigned long SampleStartTime;
unsigned long SampleDuration;	//duration of sampling in milliseconds
unsigned long LPOTotal;
float LPORatio;
		
void SMPWM01C::begin(uint8_t P1_Pin_Select, uint8_t P2_Pin_Select) 
{
	
	P1_Pin = P1_Pin_Select;
	P2_Pin = P2_Pin_Select;
  
	pinMode(P1_Pin, INPUT);      
	pinMode(P2_Pin, INPUT);
	
}

float SMPWM01C::getPM2()
{
	
	LPOTotal = 0;
	SampleStartTime = millis();
	SampleDuration = 5000;

	while((millis()-SampleStartTime) < SampleDuration)
	{
		LPODuration = pulseIn(P1_Pin, LOW);
		LPOTotal = LPOTotal+LPODuration;
	}
	
	LPORatio = LPOTotal/(SampleDuration*100); //ratio as integer percentage
	ConcentrationPM02 = 2.0699*pow(LPORatio,2)+75.123*LPORatio; // using spec sheet curve
  
	return ConcentrationPM02;
  
}