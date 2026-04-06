#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Initializes the LCD at address 0x27 (common for most) with 16 columns and 2 rows.
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

int potPin = A0;
int leftLed = 7; 
int rightLed = 2;  

unsigned long previousTime = 0;
const int blinkInterval = 300;

void setup() {
  lcd.init();          // Initializes the LCD
  lcd.backlight();     // Turns on the backlight
  myServo.attach(9);
  pinMode(leftLed, OUTPUT); 
  pinMode(rightLed, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Johnny The Maker");
}

void loop() {
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);
  myServo.write(angle);

  // Update the LCD
  lcd.setCursor(0, 1);
  lcd.print("Pot: ");
  lcd.print(potValue);
  lcd.print("   ");

  // LEDS (without delay)
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= blinkInterval) {
    previousTime = currentTime;
    if (potValue < 480) {
      digitalWrite(leftLed, !digitalRead(leftLed));
      digitalWrite(rightLed, LOW);
    } else if (potValue > 540) {
      digitalWrite(rightLed, !digitalRead(rightLed));
      digitalWrite(leftLed, LOW);
    } else {
      digitalWrite(leftLed, HIGH);
      digitalWrite(rightLed, HIGH);
    }
  }
}
