#include "happy_headers.h"

HX711 scale;


void setup() {
  // HX711
  Serial.begin(57600);
  scale.begin(dataHX711, clockHX711);

  // I2C
  LiquidCrystal_I2C lcd(0x3F,16,2);
  lcd.init();
  lcd.backlight();

  // pinModes
  pinMode(pinBottonTare, INPUT);
  pinMode(pinBottonReset, INPUT);
  pinMode(pinBotton3, INPUT);

}

void loop() {
  
}
