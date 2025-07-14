#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// HX711 variables
const uint8_t dataHX711 = 2;
const uint8_t clockHX711 = 3;

// I2C variables
cons uint8_t dataI2C = A4;
const uint8_t clockI2C = A5;

// Botton variables
const uint8_t pinBottonTare = 6; // must be changed
const uint8_t pinBottonReset = 7; // must be changed
const uint8_t pinBotton3 = 8; // must be changed





void printWeigh(float measure) {
  lcd.clear();
  int weighSpace = 4;
  int measureSpace = 4;
  int scrollTime = 400;

  if (measure < 0){
    measureSpace -= 1;
  }

  // Gramos
  if (abs(measure) >= 0 && abs(measure) < 1000){
    Serial.print("Weighing ");
    lcd.setCursor(weighSpace, 0);
    lcd.print("Weighing ");

    if (abs(measure) < 10){
      lcd.setCursor(measureSpace + 2, 1);
    }
    else if (abs(measure) < 100){
      lcd.setCursor(measureSpace + 1, 1);
    }
    else {
      lcd.setCursor(measureSpace, 1);
    }

    lcd.print(measure, 2);
    lcd.print(" g");
    Serial.print(measure, 2);
    Serial.println(" g");
  }

  // Sobrecarga
  else if (measure >= 1000 && measure < 1200){
    Serial.println("DANGER!!! REMOVE THE WEIGHT this scale cannot weigh over 1 kg");
    lcd.setCursor(1, 0);
    lcd.print("DANGER!!! REMOVE THE WEIGHT");
    lcd.setCursor(1, 1);
    lcd.print("this scale cannot weigh over 1 kg");

    
    for (int i = 0; i<20; i++){
      lcd.scrollDisplayLeft();
      delay(scrollTime);
    }
  }

  // Supercarga
  else if (measure >= 1200){
    Serial.println("REMOVE THE WEIGHT RIGHT NOW");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("REMOVE THE WEIGHT");
    lcd.setCursor(4, 1);
    lcd.print("RIGHT NOW");

    for (int i = 0; i < 24; i++){
      lcd.scrollDisplayLeft();
      delay(scrollTime);
    }
  }

  // Cero
  else {
    Serial.println("Internal Error");
    lcd.setCursor(weighSpace, 0);
    lcd.print("Weighing");
    lcd.setCursor(weighSpace, 1);
    lcd.print("Internal Error");
  }
}


void printTaring(){
  int scrollTime = 400;
  Serial.println("Taring, remove all weights");
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("TARING...   TARING...");
  lcd.setCursor(1, 1);
  lcd.print("Please remove all weights");

  for (int i = 0; i < 10; i++){
    lcd.scrollDisplayLeft();
    delay(scrollTime);
  }
}

void printTared(){
  Serial.println("Tare done, now you can put a known weight on the scale");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("TARE DONE");
}


