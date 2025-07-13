void tareScale(){
  if (scale.is_ready()){
    scale.set_scale();
    Serial.println("Taring, please remove any objects from the scale");
    lcd.print("Taring, remove weights");

    delay(5000);
    scale.tare();
    Serial.println("tare done");
    Serial.println("Put a known weight on the scale");
    delay(5000);

    long reading = scale.get_units(10);
    Serial.print("Result ");
    lcd.print("Result ");
    Serial.println(reading);
    lcd.print(reading,3);
  }
  
  else {
    Serial.println("404 HX711 not found");
    lcd.print("404 not found");
}


void printWeigh(float measure) {
  
  float kiloMeasure = measure/1000;
  float miliMeasure = measure*1000;


  // Miligramos
  if (miliMeasure > 0 && miliMeasure < 1000){
    miliMeasure = measure*1000;
    Serial.print("Weighing ");
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Weighing ");

    if (miliMeasure < 10){
      lcd.setCursor(7, 1);
    }

    else if (miliMeasure < 100){
      lcd.setCursor(6, 1);
    }

    else {
      lcd.setCursor(5, 1);
    }
    
    lcd.print(miliMeasure, 0);
    lcd.print(" mg");
    Serial.print(miliMeasure, 0);
    Serial.println(" mg");
  }

  // Gramos
  else if (measure >= 1 && measure < 1000){
    Serial.print("Weighing ");
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Weighing ");

    if (measure < 10){
      lcd.setCursor(6, 1);
    }

    else if (measure < 100){
      lcd.setCursor(5, 1);
    }

    else {
      lcd.setCursor(4, 1);
    }

    lcd.print(measure, 1);
    lcd.print(" g");
    Serial.print(measure, 1);
    Serial.println(" g");
  }

  // kilogramos
  else if (kiloMeasure >= 1 && kiloMeasure <= 50) {
    Serial.print("Weighing ");
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Weighing");
  
    if (kiloMeasure < 10){
      lcd.setCursor(5, 1);
    }
    else if (kiloMeasure < 100){
      lcd.setCursor(4, 1);
    }
    else {
      lcd.setCursor(4, 1);
    }

    lcd.print(kiloMeasure, 1);
    lcd.print(" kg");
    Serial.print(kiloMeasure);
    Serial.println(" kg");
  }

  // Sobrecarga
  else if (kiloMeasure >= 50){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("DANGER!!! REMOVE THE WEIGHT");
    
    for (int i; i>34; i++){
      lcd.setCursor(1, 1);
      lcd.print("this scale cannot weigh over 50 kg");
      lcd.scrollDisplayLeft();
      delay(500);
      if (kiloMeasure <= 50){
        break;
      }
    }
  }

  // Cero
  else {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Weighing");
    lcd.setCursor(3, 1);
    lcd.print(0);
  }
  
}
