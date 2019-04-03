// Library https://github.com/bolderflight/BME280

#include "BME280.h"


// Adafruit IO Stuff



#include "config.h"

BME280 bme(Wire,0x76);

float temperature_value;
float humidity_value;


// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature2 = io.feed("bme280-temp");
AdafruitIO_Feed *humidity2 = io.feed("bme280-humidity");

float counter;
float pause;


void setup() {


counter = 0;
//pause for x seconds between posting values
pause = 300;

  
  // put your setup code here, to run once:
Serial.begin(115200);
delay(5000);
while (!Serial){}

 // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());




if (bme.begin()<0) {
  Serial.println ("error communication with sensor!");
  while(1) {}
}

}

void loop() {
  
   io.run();
  // put your main code here, to run repeatedly


//read the sensor

bme.readSensor();
  
 // Serial.print(bme.getPressure_Pa(),2);

  temperature_value = temperature();
  humidity_value = humidity();
  
  Serial.print(temperature_value,2);
  temperature2->save(temperature_value);
  Serial.print("°C");
  Serial.print("\t");
  Serial.print(humidity_value,2);
  humidity2->save(humidity_value);
  Serial.print("%");
  Serial.print("\t");

  
  
  while (counter < pause) {
      Serial.print(".");
      counter = counter + 1;
      delay(1000);
  }
  Serial.println("");
  counter = 0;


 
}





//actually collect the values
float temperature() {

  return (bme.getTemperature_C());
  
}


float humidity() {

  return (bme.getHumidity_RH());
  
}
