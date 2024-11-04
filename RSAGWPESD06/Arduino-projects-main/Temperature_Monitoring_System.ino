const int sensorPin = A0;
const float thresholdTemp = 30.0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  if (temperatureC > thresholdTemp) {
    Serial.println("WARNING: Temperature exceeds threshold!");
  }

  delay(2000); 
}
