const int pirPin = 2;     
const int buzzerPin = 3;  
int pirState = LOW;       
unsigned long lastDetectionTime = 0; 

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected == HIGH && pirState == LOW) {
    digitalWrite(buzzerPin, HIGH); 
    lastDetectionTime = millis();  
    Serial.print("Movement detected at: ");
    Serial.print(lastDetectionTime / 1000); 
    Serial.println(" seconds");

    pirState = HIGH; // Update PIR state to HIGH
  } 
  else if (motionDetected == LOW && pirState == HIGH) {
    digitalWrite(buzzerPin, LOW); // Deactivate the buzzer
    pirState = LOW; // Update PIR state to LOW
  }
}
