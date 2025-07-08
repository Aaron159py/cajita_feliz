


void showWeight(){

}



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


void printMeasure(){
	Serial.println("Measuring");
	lcd.setCursor(0, 0);
	lcd.print("Measuring");
	lcd.setCursor(0, 1);
	lcd.print(measure);
}


