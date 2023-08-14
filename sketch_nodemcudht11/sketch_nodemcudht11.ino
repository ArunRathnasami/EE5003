#include <DHT.h>

// Constants
#define DHTPIN D4     // What digital pin the DHT sensor is connected to. You can change this.
#define DHTTYPE DHT11 // Define the type of sensor used (DHT11)

// Initialize DHT sensor 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);  // Start the serial communication at 115200 baud rate
  dht.begin();           // Initialize the DHT sensor
}

void loop() {
  // Delay between measurements. DHT11 works best at 1-minute intervals.
  delay(2000);

  // Reading temperature and humidity
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // Check if readings are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Humidity: "); 
  Serial.print(hum);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(temp);
  Serial.println(" *C");
}

