jjhvjghv

#include <DHT.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define TRIG_PIN 7
#define ECHO_PIN 8

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial espSerial(5, 6);

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float distance = getDistance();

  StaticJsonDocument<200> doc;
  doc["humidity"] = humidity;
  doc["temperature"] = temperature;
  doc["distance"] = distance;

  serializeJson(doc, espSerial);

  delay(1000);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;
  return distance;
}
