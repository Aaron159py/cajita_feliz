#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Wire.h> 
#define __DATA_SAMPLING 25

LiquidCrystal_I2C lcd(0x27,16,2);
HX711 scale;

// HX711 variables
const uint8_t dataHX711 = 2;
const uint8_t clockHX711 = 3;

// Botton variables
const uint8_t buttonReset = 8;
const uint8_t buttonTare = 9;
const uint8_t buttonElse = 10;

volatile float f, f1, f2=0, f3, f4=466970, aux1=0,aux2=0, aux3=2.91, aux5, aux6, aux7=0, i2=0, aux8;
float scales;
bool poweredup = false, block = false;
int i =0;
float med[__DATA_SAMPLING] = {0};

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

  // Internal Error
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
  Serial.println("Taring, remove weights");
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

void easterFunction(int option){
  int scrollTime = 400;
  int controlTime = 1000;
  
  switch (option){
    case 1:
      Serial.println("Beatuful Harmony");
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Beatiful");
      lcd.setCursor(4, 1);
      lcd.print("Harmony");
      delay(1000);
      break;
    
    case 2:
      Serial.println("Credits: ")
      Serial.println("Aaron Ascencio, Vicente Ahumada, Eimear Morrison, Wolfgang Vyhmeister");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("|   Aaron  | Vicente |  Eimear  |  Wolfgang  |");
      lcd.setCursor(1, 1);
      lcd.print("| Ascencio | Ahumada | Morrison | Vyhmeister |");
      
      for (int i = 0; i < 46; i++){
        lcd.scrollDisplayLeft();
        delay(scrollTime);
      }
      break;
  }
}
