#include "happy_library.h"
#include "happy_variables.h"
#include "happy_functions.h"


void setup() {
  pinMode(buttonON, HIGH);
  pinMode(buttonRESET, LOW);

  LiquidCrystal_I2C lcd(0x3F,16,2);
  lcd.init();
  lcd.backlight();
  lcd.print("echo");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  lcd.print(" s");
  delay(100);
}
