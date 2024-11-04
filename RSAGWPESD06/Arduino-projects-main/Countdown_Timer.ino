int segmentPins[] = {8, 9, 10, 11, 12, 13, A0, A1};  // Segment pins: A-G, DP
int countdownStart = 9;  // Initial countdown value
int countdown = countdownStart;
bool countdownActive = false;

const int touchSensorPin = 2;   
const int trigPin = 3;         
const int echoPin = 4;          
const int resetDistance = 10;  

unsigned long previousMillis = 0;
const long interval = 1000;  

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  pinMode(touchSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(touchSensorPin) == HIGH) {
    countdown = countdownStart;
    countdownActive = true;
  }

  if (countdownActive) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      int distance = getDistance();
      if (distance > 0 && distance <= resetDistance) {
        countdown = countdownStart;  // Reset countdown
      } else {
        countdown--;  // Decrease countdown
      }

      if (countdown < 0) {
        displayError();  // Show "E" on display
        countdownActive = false;  // Stop countdown
      } else {
        displayNumber(countdown);  // Display countdown value
      }
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void displayNumber(int number) {
  byte numbers[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 1, 0, 1, 1}   // 9
  };

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[number][i] ? LOW : HIGH); 
  }
}

void displayError() {

  byte errorPattern[7] = {1, 0, 0, 1, 1, 1, 1};

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], errorPattern[i] ? LOW : HIGH);  // LOW for ON, HIGH for OFF in common anode
  }
}
