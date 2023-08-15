#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available()) {
    StaticJsonDocument<300> doc;
    DeserializationError error = deserializeJson(doc, Serial);

    if (!error) {
      float humidity = doc["humidity"];
      float temperature = doc["temperature"];
      float current = doc["current"];
      float distance = doc["distance"];

      // Use the data (e.g., send it to a cloud service, MQTT, etc.)

      Serial.print("Received Humidity: ");
      Serial.println(humidity);
      Serial.print("Received Temperature: ");
      Serial.println(temperature);
      Serial.print("Received Current: ");
      Serial.println(current);
      Serial.print("Received Distance: ");
      Serial.println(distance);
      Serial.println("-----------------------------------------");
    } else {
      Serial.println("Failed to parse data!");
    }
  }
}

