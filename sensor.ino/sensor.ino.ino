// Library https://github.com/bolderflight/BME280

#include "BME280.h"



BME280 bme(Wire,0x76);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
while (!Serial){}

if (bme.begin()<0) {
  Serial.println ("error communication with sensor!");
  while(1) {}
}

}

void loop() {
  // put your main code here, to run repeatedl

//read the sensor

bme.readSensor();
  
  Serial.print(bme.getPressure_Pa(),2);
  Serial.print("pa");
  Serial.print("\t");
  Serial.print(bme.getTemperature_C(),2);
  Serial.print("°C");
  Serial.print("\t");
  Serial.print(bme.getHumidity_RH(),2);
  Serial.println("%");
  
  
  delay(1000);


  
}
