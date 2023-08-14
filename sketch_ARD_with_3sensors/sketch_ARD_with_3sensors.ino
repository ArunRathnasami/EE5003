#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define ACS_PIN A1
#define TRIGGER_PIN 7
#define ECHO_PIN 8

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float current = readACS712();
  float distance = readUltrasonic();

  StaticJsonDocument<250> doc;
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["current"] = current;
  doc["distance"] = distance;

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

float readUltrasonic() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;

  return distance;
}
