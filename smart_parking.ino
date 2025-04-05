#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD initialization
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo;

#define ir_enter 2
#define ir_back 4
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

// Fire alarm
int flamepin = A2;   // Flame sensor pin
int buzpin = 11;     // Buzzer pin
int threshold = 200; // Sets threshold value for flame sensor
int flamesensvalue = 0; // Initialize flame sensor reading

int slot = 6; // Maximum number of parking slots (starts at 6)

int carEntering = 0;  // Flag for car entering
int carExiting = 0;   // Flag for car exiting


void setup() {
   Serial.begin(9600);
  
  // Initialize pins
  pinMode(flamepin, INPUT);
  pinMode(buzpin, OUTPUT);
  
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);
  
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
  
  myservo.attach(3);
  myservo.write(90);  // Start gate closed
  
  // LCD initialization
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(2, 1);
  lcd.print("Smart Car Parking");
  lcd.setCursor(5, 2);
  lcd.print(" System...");
  delay(2000);
  lcd.clear();
  
  // Read sensor data
  updateAvailableSlots();
  displaySlotStatus();  // Show initial slot status

}

void loop() {
    // Fire detection logicer
  flamesensvalue = analogRead(flamepin); 
  Serial.println(flamesensvalue);// Reads analog data from flame sensor
  if (flamesensvalue <= threshold) {     // If flame is detected
    tone(buzpin, 1000);                  // Activate buzzer with a 1kHz tone
    delay(1000);                         // Wait 1 second
  } else {
    noTone(buzpin);                      // Stop the buzzer
  }
  
  // Parking slot display
  updateAvailableSlots();  // Continuously update the number of available slots based on slot sensors
  displaySlotStatus();     // Continuously update the display

  // Entry gate control: Open gate if car comes to entrance sensor and slots are available

  if (digitalRead(ir_enter) == 0 && carEntering == 0 && carExiting == 0) {
    if (slot > 0) {
      myservo.write(180);  // Open gate
      carEntering=1;     // Car is entering
    } else {
      // If parking is full, display "Park is full"
      lcd.setCursor(0, 0);
      lcd.print("Sorry, Park is full!");
      delay(1500);        // Wait before clearing the message
    }
  }
  
  // Close gate after car passes the back sensor (it has entered)
  if (carEntering == 1 && digitalRead(ir_back) == 0) {
    myservo.write(90);    // Close gate
    carEntering = 0;      // Reset flag for next car
    slot--;                // Decrease slot count
    delay(1000);
  }

  // Exit gate control: Open gate when car comes to back sensor for exit
  if (digitalRead(ir_back) == 0 && carExiting == 0 && slot < 6) {
    myservo.write(180);   // Open gate for exit
    carExiting = 1;       // Car is exiting
  }

  // Close gate after car passes the entrance sensor (car has exited)
  if (carExiting == 1 && digitalRead(ir_enter) == 0) {
    myservo.write(90);    // Close gate
    carExiting = 0;       // Reset flag for next car
    slot++;                // Increase slot count
    delay(1000);
  }
  
  delay(100);  // Small delay for stability and smoother sensor readings
}

// Function to update available slot count based on the slot sensors
void updateAvailableSlots() {
  int filledSlots = 0;

  // Check each parking slot sensor and count how many are filled
  if (digitalRead(ir_car1) == 0) { filledSlots++; }
  if (digitalRead(ir_car2) == 0) { filledSlots++; }
  if (digitalRead(ir_car3) == 0) { filledSlots++; }
  if (digitalRead(ir_car4) == 0) { filledSlots++; }
  if (digitalRead(ir_car5) == 0) { filledSlots++; }
  if (digitalRead(ir_car6) == 0) { filledSlots++; }

  // Update available slots based on the number of filled slots
  slot = 6 - filledSlots;
}

// Function to display slot status and available slots on the LCD
void displaySlotStatus() {
  lcd.clear();  // Clear the display

  // Display available slots
  lcd.setCursor(2, 0);
  lcd.print("Available slots:");
  lcd.print(slot);
  
  // Display the status of each slot
  lcd.setCursor(2, 1);
  lcd.print(digitalRead(ir_car1) == 0 ? "S1: FILL " : "S1:Empty ");
  lcd.print(digitalRead(ir_car2) == 0 ? "S2: FILL " : "S2:Empty ");
  
  lcd.setCursor(2, 2);
  lcd.print(digitalRead(ir_car3) == 0 ? "S3: FILL " : "S3:Empty ");
  lcd.print(digitalRead(ir_car4) == 0 ? "S4: FILL " : "S4:Empty ");

  lcd.setCursor(2, 3);
  lcd.print(digitalRead(ir_car5) == 0 ? "S5: FILL " : "S5:Empty ");
  lcd.print(digitalRead(ir_car6) == 0 ? "S6: FILL " : "S6:Empty ");

}
