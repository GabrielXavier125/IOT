#include <LiquidCrystal.h>

// Pinos dos LEDs
const int led1Pin = 7; // Verde
const int led2Pin = 8; // Amarelo
const int led3Pin = 9; // Vermelho

// Pinos do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Estado atual dos LEDs
bool led1State = false;
bool led2State = false;
bool led3State = false;

void setup() {
  Serial.begin(9600);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("LED Status:");
  updateLCD();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'A': led1State = true; break;
      case 'a': led1State = false; break;
      case 'B': led2State = true; break;
      case 'b': led2State = false; break;
      case 'C': led3State = true; break;
      case 'c': led3State = false; break;
    }

    // Atualiza LEDs físicos
    digitalWrite(led1Pin, led1State ? HIGH : LOW);
    digitalWrite(led2Pin, led2State ? HIGH : LOW);
    digitalWrite(led3Pin, led3State ? HIGH : LOW);

    // Atualiza LCD
    updateLCD();
  }
}

void updateLCD() {
  lcd.setCursor(0, 1); // Linha 2
  lcd.print("1:");
  lcd.print(led1State ? "ON " : "OFF");
  lcd.print("2:");
  lcd.print(led2State ? "ON " : "OFF");
  lcd.print("3:");
  lcd.print(led3State ? "ON " : "OFF");
}
