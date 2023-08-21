#define TRIGGERPIN D5
#define ECHOPIN D6
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int screenWidth = 16;
int screenHeight = 2;

int stringStart, stringEnd = 0;
int scrollCursor = screenWidth;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.begin(screenWidth, screenHeight);

}

void loop() {

      

  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  Serial.print(distance*0.39307);
  Serial.println("Inch");

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  

  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  
  lcd.setCursor(9, 0);
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(9, 1);
  lcd.print(distance*0.39307);
  lcd.print(" cm");


  delay(2000);

}
