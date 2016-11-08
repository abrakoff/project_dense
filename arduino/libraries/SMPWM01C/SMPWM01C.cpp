#include "SMPWM01C.h"

SMPWM01C::SMPWM01C() {}
		
void SMPWM01C::begin(uint8_t PM2_Pin_Select, uint8_t PM10_Pin_Select) 
{
	
	//Setup up PM2 and PM10 pins into Arduino
	PM2_Pin = PM2_Pin_Select;
	PM10_Pin = PM10_Pin_Select;
  
	//Set pin modes to input
	pinMode(PM2_Pin, INPUT);      
	pinMode(PM10_Pin, INPUT);
	
}

float SMPWM01C::getPM2()
{
	//float PreviousPM2Concentration = PM2Concentration;
	
	//Variables for calculation of LPO and determining dust concentration
	//Set SampleDuration between 5000 and 30000 milliseconds
	LPOTotal = 0;
	SampleStartTime = millis();
	SampleDuration = 30000;

	//For sampling duration, count total time pin is spent low (detecting particles)
	//Total LPO is the sum of time spent low
	while((millis()-SampleStartTime) < SampleDuration)
	{
		LPODuration = 0;
		LPODuration = pulseIn(PM2_Pin, LOW, (SampleDuration-(millis()-SampleStartTime))*1000);
		LPOTotal = LPOTotal+(LPODuration/1000);
	}
	
	//Convert LPO to percentage time, use curve fit from spec sheet to determine PM2.5 Concentration
	LPORatio = (LPOTotal/SampleDuration)*100; //ratio as a percentage
	PM2Concentration = -0.1609*pow(LPORatio,3)+7.3164*pow(LPORatio,2)+37.02*LPORatio; // using spec sheet curve

	//PM2Concentration = (PreviousPM2Concentration+PM2Concentration*(FILTER_WEIGHT-1.0))/FILTER_WEIGHT;
  
	return PM2Concentration;
}

float SMPWM01C::getPM10()
{
	//float PreviousPM10Concentration = PM10Concentration;
	
	//Variables for calculation of LPO and determining dust concentration
	//Set SampleDuration between 5000 and 30000 milliseconds
	LPOTotal = 0;
	SampleStartTime = millis();
	SampleDuration = 30000;

	//For sampling duration, count total time pin is spent low (detecting particles)
	//Total LPO is the sum of time spent low
	while((millis()-SampleStartTime) < SampleDuration)
	{
		LPODuration = 0;
		LPODuration = pulseIn(PM10_Pin, LOW, (SampleDuration-(millis()-SampleStartTime))*1000);
		LPOTotal = LPOTotal+(LPODuration/1000);
	}
	
	//Convert LPO to percentage time, use curve fit from spec sheet to determine PM10 Concentration
	LPORatio = (LPOTotal/SampleDuration)*100; //ratio as a percentage
	PM10Concentration = -0.1609*pow(LPORatio,3)+7.3164*pow(LPORatio,2)+37.02*LPORatio; 
	
	//PM10Concentration = (PreviousPM10Concentration+PM10Concentration*(FILTER_WEIGHT-1.0))/FILTER_WEIGHT;
  
	return PM10Concentration;
}