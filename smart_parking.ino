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

void setup() {
  lcd.begin(16, 2);
  gate.attach(A2);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_exit, INPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(buzzer, OUTPUT);

  gate.write(0);
}
void loop() {
  int flame = digitalRead(flame_sensor);
  if (flame == 1) {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("FIRE");
  } else {
    digitalWrite(buzzer, LOW);
  }
}
