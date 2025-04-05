#include <Servo.h>
#include <LiquidCrystal.h>

// Define LCD pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define Servo
Servo gate;

// Define Sensor and Actuator Pins
const int ir1 = 8;
const int ir2 = 9;
const int ir3 = 10;
const int ir4 = 11;
const int irEnter = 12;
const int irExit = 13;
const int flameSensor = A0;
const int buzzer = A1;

int totalSlots = 4;
void setup() {
  lcd.begin(16, 2);
  gate.attach(A2);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(irEnter, INPUT);
  pinMode(irExit, INPUT);
  pinMode(flameSensor, INPUT);
  pinMode(buzzer, OUTPUT);

  gate.write(0); // Gate closed
  void welcomeMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Smart Parking ");
  lcd.setCursor(0, 1);
  lcd.print("System Started");
  delay(2000);
  lcd.clear();
}

}
