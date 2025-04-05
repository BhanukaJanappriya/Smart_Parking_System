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
