#include "happy_functions.h"

void setup(){
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);
  scale.begin(dataHX711, clockHX711);
  pinMode(buttonReset,INPUT_PULLUP);
  pinMode(buttonTare,INPUT_PULLUP);
  pinMode(buttonEaster,INPUT_PULLUP);
  scale.set_scale(730.15);    
}

void loop(){  
  //tare inicial y variables de seteo iniciales como la calibracion
  if (!poweredup) {
    f = scale.read_average(25);
    scales = 731.02;
    poweredup = true;
    med[0] = scale.read();
    f2+=med[0];
    i++;
  }

  //codigo de promedio dinamico
  f2-=med[i];     
  med[i] = scale.read();
  f2+=med[i];
  i= (i+1)%__DATA_SAMPLING;
  f1=f2/__DATA_SAMPLING;

  aux5=aux2;
  //transforma la lectura desnuda a la lectura en gramos, calcula la diferencia de la lectura anterior y la nueva para el diferencial usado despues (fluctuaciones)
  aux2 = (f1-f4)/scales - aux3;
  aux1= aux5-aux2;
  aux6 = abs(aux1);

  if (block) {
    aux8 = trunc(aux7);
  } else {
    aux8 = trunc(aux2 * 100.0);
  }

  //superbloque para el bloqueo de la lectura y optimizacion de las fluctuaciones
  if (i%5==0) {         
    printWeigh(aux8/100);
    if (aux7==aux8) {
      i2++;
    } else {
      i2=0;
    }
    
    if (i2==2) {
      block = true;
      i=0;
    }
    aux7=aux8;
  }

  if (abs(aux1)>0.01) {
    block = false;
  }
  if (abs(aux2*100-aux7)>4) {
    block = false;
  }                          
  //termino del superbloque
  
  //reset
  if (!digitalRead(buttonReset)) {
      aux3=aux2+aux3;
      block = false; 
  }

  //tare
  if (!digitalRead(buttonTare)) {
    i = 0;
    f = scale.read_average(20);
    for (int j = 0; j<__DATA_SAMPLING; j++) {
      med[j] = 0;
    }
    med[0] = scale.read();
    f2+=med[0];
    i++;
  }
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
      
      for (int i; i < 46; i++){
        lcd.scrollDisplayLeft();
        delay(scrollTime);
      }
      break;
  }
}
