#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servo1;
LiquidCrystal_I2C lcd(0x27,16,2);

int button1 = 2;
int button2 = 4;

int led1 = 5;
int led2 = 6;
int buzzer = 7;
int led3 = 8;

int echoPin = 9;
int trigPin = 10;

int red = 11;
int green = 12;
int blue = 13;

int pot = A0;
int ldr = A1;
int temp = A2;
int soil = A3;

void setup()
{
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  servo1.attach(3);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  // Buttons
  digitalWrite(led1, !digitalRead(button1));
  digitalWrite(led2, !digitalRead(button2));

  // Servo
  int angle = map(analogRead(pot),0,1023,0,180);
  servo1.write(angle);

  // LDR
  int light = analogRead(ldr);

  if(light < 400)
    digitalWrite(led3,HIGH);
  else
    digitalWrite(led3,LOW);

  // Ultrasonic
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);

  long duration = pulseIn(echoPin,HIGH);
  int distance = duration * 0.034 / 2;

  if(distance < 20)
    digitalWrite(buzzer,HIGH);
  else
    digitalWrite(buzzer,LOW);

  // Temperature
  float voltage = analogRead(temp) * 5.0 / 1023.0;
  float temperature = (voltage - 0.5) * 100;

  // Soil sensor and RGB LED
  int moisture = analogRead(soil);

  if(moisture < 400)
  {
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);
  }
  else
  {
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(blue,LOW);
  }

  // LCD
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print((int)temperature);
  lcd.print("C ");

  lcd.setCursor(0,1);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm ");

  delay(300);
}