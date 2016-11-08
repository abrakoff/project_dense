#include "SMPWM01C.h"

SMPWM01C::SMPWM01C() {}
		
void SMPWM01C::begin(uint8_t PM2_Pin_Select, uint8_t PM10_Pin_Select) 
{
	
	PM2_Pin = PM2_Pin_Select;
	PM10_Pin = PM10_Pin_Select;
  
	pinMode(PM2_Pin, INPUT);      
	pinMode(PM10_Pin, INPUT);
	
}

float SMPWM01C::getPM2()
{
	float PreviousPM2Concentration = PM2Concentration;
	
	LPOTotal = 0;
	SampleStartTime = millis();
	SampleDuration = 30000;

	while((millis()-SampleStartTime) < SampleDuration)
	{
		LPODuration = 0;
		LPODuration = pulseIn(PM2_Pin, LOW, (SampleDuration-(millis()-SampleStartTime))*1000);
		LPOTotal = LPOTotal+LPODuration;
	}
	
	LPOTotal = LPOTotal/1000;
	LPORatio = (LPOTotal/SampleDuration)/100; //ratio as a percentage
	PM2Concentration = -0.1248*pow(LPORatio,3)+6.3746*pow(LPORatio,2)+42.337*LPORatio; // using spec sheet curve

	PM2Concentration = (PreviousPM2Concentration+PM2Concentration*(FILTER_WEIGHT-1.0))/FILTER_WEIGHT;
  
	return PM2Concentration;
}

float SMPWM01C::getPM10()
{
	float PreviousPM10Concentration = PM10Concentration;
	
	LPOTotal = 0;
	SampleStartTime = millis();
	SampleDuration = 30000;

	while((millis()-SampleStartTime) < SampleDuration)
	{
		LPODuration = 0;
		LPODuration = pulseIn(PM10_Pin, LOW, (SampleDuration-(millis()-SampleStartTime))*1000);
		LPOTotal = LPOTotal+LPODuration;
	}
	
	LPOTotal = LPOTotal/1000;
	LPORatio = (LPOTotal/SampleDuration)/100; //ratio as a percentage
	PM10Concentration = -0.1248*pow(LPORatio,3)+6.3746*pow(LPORatio,2)+42.337*LPORatio; // using spec sheet curve
	
	PM10Concentration = (PreviousPM10Concentration+PM10Concentration*(FILTER_WEIGHT-1.0))/FILTER_WEIGHT;
  
	return PM10Concentration;
}