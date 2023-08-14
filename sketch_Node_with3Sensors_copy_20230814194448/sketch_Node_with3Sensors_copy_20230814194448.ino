#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial arduinoSerial(D5, D6); // D5=RX, D6=TX

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600);
  delay(2000);
}

void loop() {
  if (arduinoSerial.available()) {
    String jsonData = arduinoSerial.readStringUntil('\n');
    
    StaticJsonDocument<250> doc;
    DeserializationError error = deserializeJson(doc, jsonData);
    
    if (!error) {
      float humidity = doc["humidity"];
      float temperature = doc["temperature"];
      float current = doc["current"];
      float distance = doc["distance"];

      Serial.println("Received from Arduino:");
      Serial.print("Humidity: "); Serial.println(humidity);
      Serial.print("Temperature: "); Serial.println(temperature);
      Serial.print("Current: "); Serial.println(current);
      Serial.print("Distance: "); Serial.println(distance);
    } else {
      Serial.println("Failed to parse JSON from Arduino!");
    }
  }
}
