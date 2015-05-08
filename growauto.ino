#include "Arduino.h"
#include "DHT.h"
#include <LiquidCrystal.h>

// PIN's being used
#define DHTPIN 2        // humidity + temperature sensor
#define LHTPIN A0       // light sensor
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// the type of humidity sensor we are using
#define DHTTYPE DHT22   // also, AM2302

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  dht.begin();       // begin reading temperature and humidity
}

void loop() {
  delay(2000); // only calculate new values every 2 seconds
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();     // humidity as %
  float t = dht.readTemperature();  // temperature as Celsius
  float l = analogRead(LHTPIN);     // light value
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  String LCDstr1;              // first line on LCD;
  LCDstr1 += h;                // humidity,
  LCDstr1 += "% ";
  LCDstr1 += t;                // temperature
  LCDstr1 += "C ";
  
  String LCDstr2;              // second line on LCD;
  LCDstr2 += l;                // light value,
  LCDstr2 += " ";
  LCDstr2 += millis() / 1000;  // number of seconds since reset
  
  lcd.setCursor(0, 0);         // cursor to column 0, line 0
  lcd.print(LCDstr1);           
  lcd.setCursor(0, 1);         // cursor to column 0, line 1
  lcd.print(LCDstr2);  
}


