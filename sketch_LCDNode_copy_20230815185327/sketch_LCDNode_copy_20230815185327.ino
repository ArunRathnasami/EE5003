#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <WiFi.h>

const char THING_ID[] = "b5666412-b34b-4504-b724-07381a397daa";

float temperature;
float humidity;
float current;
float distance;

const char* ssid = "Batmobile";
const char* password = "qwerty123";

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the ArduinoIoTCloud
  initArduinoIoTCloud();

  // Set up your connections
  setConnectionHandler(&ArduinoIoTPreferredConnection);

  // Begin the cloud connection
  ArduinoCloud.begin(THING_ID);
}

void loop() {
  ArduinoCloud.update();

  // Your code to read sensor data and other operations
  
  // Update the cloud variables
  ArduinoCloud.setFloat(temperature, "temperature");
  ArduinoCloud.setFloat(humidity, "humidity");
  ArduinoCloud.setFloat(current, "current");
  ArduinoCloud.setFloat(distance, "distance");
}
