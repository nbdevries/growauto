#include "Arduino.h"
#include <DHT.h>
#include <LiquidCrystal.h>

// PIN's being used
#define DHTPIN 2        // humidity + temperature sensor
#define LHTPIN A0       // light sensor
#define BT1PIN 12       // button 1
#define BT2PIN 11       // button 2
LiquidCrystal lcd(7, 8, 3, 4, 5, 6); // LCD's PINs

// the type of humidity sensor we are using
#define DHTTYPE DHT22   // also, AM2302

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);


// Global Variables
// readings
float minHmdt = 1000; // max and min humidity
float maxHmdt = 0;
float minTemp = 1000; // max and min temperature
float maxTemp = 0;

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
  
  minHmdt = min(minHmdt, h);  // determine min/max values
  maxHmdt = max(maxHmdt, h);
  minTemp = min(minTemp, t);
  maxTemp = max(maxTemp, t);
   
  String LCDstr1;  // first line on LCD;
  String LCDstr2;  // second line on LCD;
  
  // display values depending on buttons pressed
  if (digitalRead(BT1PIN) == HIGH) {  // when button 1 is pushed down, display;
    LCDstr1 += maxHmdt;               // max humidity,
    LCDstr1 += "% ";
    LCDstr1 += maxTemp;               // max temperature,
    LCDstr1 += "C ";
    LCDstr2 += minHmdt;               // min humidity,
    LCDstr2 += "% ";
    LCDstr2 += minTemp;               // min temperature 
    LCDstr2 += "C ";
  } else
  if (digitalRead(BT2PIN) == HIGH) {  // when button 2 is pushed down, display:
    LCDstr1 += l;                      // light value,
    LCDstr2 += millis() / 1000;        // seconds since last reset
  } else {               // Default display (no buttons pushed);
    LCDstr1 += h;        // current humidity,
    LCDstr1 += "% ";
    LCDstr1 += t;        // current temperature,
    LCDstr1 += "C ";
    LCDstr2 += minHmdt;  // min humidity,
    LCDstr2 += "% ";
    LCDstr2 += minTemp;  // min temperature 
    LCDstr2 += "C ";
  }
  
  lcd.clear(); // clear LCD 
  // write to LCD
  lcd.setCursor(0, 0);         // cursor to column 0, line 0
  lcd.print(LCDstr1);           
  lcd.setCursor(0, 1);         // cursor to column 0, line 1
  lcd.print(LCDstr2);  
}
