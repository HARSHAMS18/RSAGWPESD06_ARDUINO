#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ssButton = 9;
int resButton = 8;

unsigned long startMillis, Sec, Min;

void setup() {
  lcd.begin(16, 2);
  pinMode(ssButton, INPUT);
  pinMode(resButton, INPUT);
  Serial.begin(9600);
  lcd.setCursor(3,0);
  lcd.print("STOPWATCH");
  lcd.setCursor(5,1);
  lcd.print("00:00");
}

void loop() {
  int val1 = digitalRead(ssButton);
  int val2 = digitalRead(resButton);
  if(digitalRead(ssButton) == 1){
    delay(200);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("STOPWATCH");
    lcd.setCursor(5,1);
    lcd.print("00:00");
    startMillis = millis();
    while(1){
      if(digitalRead(ssButton) == 1 || digitalRead(resButton) == 1){
        delay(200);
        break;
      }
      Sec = ((millis()-startMillis)/1000)%60;
      Min = ((millis()-startMillis)/60000)%60;
      lcd.setCursor(5,1);
      if(Min<10){
        lcd.print("0");
        lcd.print(Min);
      }
      else{
        lcd.print(Min);
      }
      lcd.print(":");
      if(Sec<10){
        lcd.print("0");
        lcd.print(Sec);
      }
      else{
        lcd.print(Sec);
      }
    }
  }
  if(digitalRead(resButton) == 1){
    lcd.setCursor(5,1);
    lcd.print("00:00");
  }
}
