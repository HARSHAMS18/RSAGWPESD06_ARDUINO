const int trigPin = 9;
const int echoPin = 10;
const int touchPin = 11;

const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;

const int dig1 = 12;
const int dig2 = 13;
const int dig3 = 14;
const int dig4 = 15;

const int segments[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 0, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 0, 0, 1, 0, 1},  // 3
  {0, 1, 1, 0, 0, 0, 1},  // 4
  {1, 0, 1, 0, 1, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 0, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 0, 1, 1, 1}   // 9
};

int count = 0;                    
bool lastState = false;           
const int distanceThreshold = 20; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(touchPin, INPUT);
  
  for (int i = 0; i < 7; i++) {
    pinMode(segA + i, OUTPUT);
  }

  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Distance in cm

  if (distance < distanceThreshold) {
    if (!lastState) {
      count++;             
      lastState = true;     
      Serial.print("Count: ");
      Serial.println(count);
    }
  } else {
    lastState = false;   
  }
  
  if (digitalRead(touchPin) == HIGH) {
    count = 0;              
    Serial.println("Count reset");
  }
  
  displayNumber(count);

  delay(5); // Small delay to stabilize multiplexing
}

void displayNumber(int num) {
  
  int digits[4] = {0, 0, 0, 0};  // Array to hold each digit
  digits[0] = num / 1000 % 10;   // Thousands place
  digits[1] = num / 100 % 10;    // Hundreds place
  digits[2] = num / 10 % 10;     // Tens place
  digits[3] = num % 10;          // Units place
  
  for (int i = 0; i < 4; i++) {
    clearDisplay();             
    showDigit(digits[i]);       
    
    digitalWrite(dig1 + i, HIGH);
    delay(5);                   

    digitalWrite(dig1 + i, LOW);
  }
}

void showDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segA + i, segments[num][i]);
  }
}

void clearDisplay() {
  // Turn off all segments
  for (int i = 0; i < 7; i++) {
    digitalWrite(segA + i, LOW);
  }
}
