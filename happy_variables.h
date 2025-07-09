// PIN Variables start with pin


// HX711 variables
const uint8_t pinGND_hx711 = GND; // must be changed
const uint8_t pinDT_hx711 = 2;
const uint8_t pinSCK_hx711 = 3;
const uint8_t pinVCC_hx711 = 5V; // must be changed


// I2C variables
const uint8_t pinGND_i2c = GND; //must be changed
const uint8_t pinVCC_i2c = 5V;
cons uint8_t pinSDA_i2c = A4;
const uint8_t pinSCL_i2c = A5;

// Botton variables
const uint8_t pinBottonTare = 6; // must be changed
const uint8_t pinBottonReset = 7; // must be changed
const uint8_t pinBotton3 = 8; // must be changed



// else variables
float tareValue = 0.0;
float measure = 0.0;
