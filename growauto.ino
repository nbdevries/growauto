#include "DHT.h"

// PIN's being used.
#define DHTPIN 2        // humidity + temperature sensor
#define LHTPIN A0       // light sensor

// the type of humidity sensor we are using
#define DHTTYPE DHT22   // also, AM2302

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  dht.begin();
}

void loop() {
  
  // only calculate new values every 2 seconds
  delay(2000);
  
  float temp = analogRead(lightSnsrPIN);
  Serial.print("Light value: ");
  Serial.println(temp);
}


