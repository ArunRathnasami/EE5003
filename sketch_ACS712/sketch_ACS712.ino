const int ACS_PIN = A1; // Define the analog input pin where the sensor is connected

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
  delay(1000);        // Allow some time for the sensor to stabilize
  Serial.println("ACS712 Current Sensor Test");
}

void loop() {
  float current = readACS712(); // Read the current value from the ACS712 sensor
  Serial.print("Current: ");
  Serial.print(current, 2); // Print the current value with 2 decimal places
  Serial.println(" A");
  delay(1000);  // Wait for a second before reading again
}

float readACS712() {
  int raw = analogRead(ACS_PIN); // Read the raw ADC value
  float voltage = (raw / 1023.0) * 5.0; // Convert ADC reading to voltage
  
  // Assuming sensor with 5A rating and 185mV/A output
  float zero = 2.5; // Sensor's zero point (when no current flows, it should output half of the supply voltage, which is 2.5V for 5V supply)
  float sensitivity = 0.185; // Sensitivity factor for 5A sensor (185mV/A)

  float current = (voltage - zero) / sensitivity; // Calculate current value
  return current;
}

