#include <SMPWM01C.h>

SMPWM01C DustSensor;

void setup() {
 
  Serial.begin(9600);

  DustSensor.begin(4,5);

}

void loop() {
  
  //Print the small particle concentration, 1-3um in size
  //Measurement (should be) in ug/m^3
  Serial.print("PM2.5: ");
  Serial.println(DustSensor.getPM2());
  
  //Print the large particle concentration, ~10um in size
  //Measurement (should be) in ug/m^3
  Serial.print("PM10: ");
  Serial.println(DustSensor.getPM10());
  
}
