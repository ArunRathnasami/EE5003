#include "ArduinoIoTCloud.h"
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

#define DHTPIN A1
#define DHTTYPE DHT11
#define ACS_PIN A0
#define TRIG_PIN 7
#define ECHO_PIN 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;
float current;
float distance;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(16, 2);
  delay(2000);

  ArduinoCloud.setThingId("your_thing_id");
  ArduinoCloud.addProperty(temperature, READ, "Temperature", "C");
  ArduinoCloud.addProperty(humidity, READ, "Humidity", "%");
  ArduinoCloud.addProperty(current, READ, "Current", "A");
  ArduinoCloud.addProperty(distance, READ, "Distance", "cm");

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  current = readACS712();
  distance = readUltrasonicDistance();

  // Display data on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm");

  ArduinoCloud.update();
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



