#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo gate;

int ir1 = 8;
int ir2 = 9;
int ir3 = 10;
int ir4 = 11;
int ir_enter = 12;
int ir_exit = 13;
int flame_sensor = A0;
int buzzer = A1;
int totalSlot = 4;

void setup() {
  lcd.begin(16, 2);
  gate.attach(A2);
}
