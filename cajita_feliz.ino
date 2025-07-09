#include "happy_library.h"
#include "happy_variables.h"
#include "happy_functions.h"


HX711 scale;

void setup() {
  
  Serial.begin(57600);
  scale.begin(pinDT_hx711, pinSCK_hx711);


  LiquidCrystal_I2C lcd(0x3F,16,2);
  lcd.init();
  lcd.backlight();
  lcd.print("echo");

  // pinModes
  pinMode(pinBottonTare, INPUT);
  pinMode(pinBottonReset, INPUT);
  pinMode(pinBotton3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(" s");
  delay(100);
  


  if (analogRead(pinBottonTare)){
    tareScale();
  }


  if (analogRead(pinBottonReset)){














}
