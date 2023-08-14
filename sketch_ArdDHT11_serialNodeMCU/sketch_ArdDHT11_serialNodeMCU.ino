#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial arduinoSerial(D5, D6);

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600);
}

void loop() {
  if (arduinoSerial.available()) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, arduinoSerial);

    if (!error) {
      float humidity = doc["humidity"];
      float temperature = doc["temperature"];
      float distance = doc["distance"];

      Serial.print("Humidity: ");
      Serial.println(humidity);
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.print("Distance: ");
      Serial.println(distance);
      Serial.println("------------------------------");
    } else {
      Serial.println("Failed to read JSON");
    }
  }
}
