#include "DHT.h"
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

#define DHTPIN A1
#define DHTTYPE DHT11
#define ACS_PIN A0
#define TRIG_PIN 7
#define ECHO_PIN 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(16, 2);
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float current = readACS712();
  float distance = readUltrasonicDistance();

  // Display data on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm");
  
  // Create a JSON document to hold our sensor readings
  StaticJsonDocument<300> doc;
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["current"] = current;
  doc["distance"] = distance;

  // Serialize JSON and print to serial
  serializeJson(doc, Serial);
  Serial.println();

  delay(1000);
}

float readACS712() {
  int raw = analogRead(ACS_PIN);
  float voltage = (raw / 1023.0) * 5.0; 
  float zero = 2.5;  
  float sensitivity = 0.185;  

  float current = (voltage - zero) / sensitivity;
  return current;
}

float readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}
