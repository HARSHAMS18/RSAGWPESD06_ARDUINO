const int irSensor1Pin = 2; 
const int irSensor2Pin = 3; 
const int trigPin = 4;       
const int echoPin = 5;       
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12};

int count = 0;
bool irSensor1State = LOW;
bool irSensor2State = LOW;
bool lastIrSensor1State = LOW;
bool lastIrSensor2State = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(irSensor1Pin, INPUT);
    pinMode(irSensor2Pin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
    displayCount(count);
}

void loop() {
    irSensor1State = digitalRead(irSensor1Pin);
    irSensor2State = digitalRead(irSensor2Pin);

    // Check if IR Sensor 1 is triggered first
    if (irSensor1State == HIGH && lastIrSensor1State == LOW) {
        delay(50); // Debounce delay
        if (digitalRead(irSensor2Pin) == LOW) {
            // Confirm direction using ultrasonic sensor
            long duration = measureDistance();
            if (duration > 0) {
                count++; // Person entered
                displayCount(count);
            }
        }
    }

    // Check if IR Sensor 2 is triggered first
    if (irSensor2State == HIGH && lastIrSensor2State == LOW) {
        delay(50); // Debounce delay
        if (digitalRead(irSensor1Pin) == LOW) {
            // Confirm direction using ultrasonic sensor
            long duration = measureDistance();
            if (duration > 0) {
                count--; // Person exited
                displayCount(count);
            }
        }
    }

    // Update last states
    lastIrSensor1State = irSensor1State;
    lastIrSensor2State = irSensor2State;
}

long measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(echoPin, HIGH) * 0.034 / 2; 
}

void displayCount(int count) {
    count = constrain(count, 0, 99);
    int tens = count / 10; 
    int ones = count % 10; 

    // Display tens digit
    displayDigit(tens, segmentPins[0]);
    displayDigit(ones, segmentPins[1]);
}

void displayDigit(int digit, int segmentPin) {
    const byte segmentMap[10] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };
    
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], LOW);
    }

    // Activate the segments for the current digit
    byte segments = segmentMap[digit];
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], segments & (1 << i) ? HIGH : LOW);
    }
}
