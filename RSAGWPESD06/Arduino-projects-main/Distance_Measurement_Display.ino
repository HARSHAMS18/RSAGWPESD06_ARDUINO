#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

Adafruit_7segment display = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  display.begin(0x70);
  display.setBrightness(5); 
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10000) { 
    display.print(distance); 
  } else {
    display.print(9999); 
  }

  display.writeDisplay();
  delay(500); 
}
