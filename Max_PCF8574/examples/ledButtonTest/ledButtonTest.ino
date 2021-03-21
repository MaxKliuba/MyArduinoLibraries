#include <Max_PCF8574.h>

/*
 * ATtiny85:
 *  SDA_PIN 0 // pullup (10kOm to VCC)
 *  SCL_PIN 2 // pullup (10kOm to VCC)
 * 
 * Arduino:
 *  SDA_PIN A4
 *  SCL_PIN A5
 *  
 * ESP8266:
 *  SDA_PIN GPIO4
 *  SCL_PIN GPIO5
 */
 
#define PCF8574_ADDRESS (0x20) // A0 - A1 - A2 (pins on PCF8574) are connected to GND

#define LED_PIN 0 // (PCF8574 (0))--[R >= 330 Om]--(-)|LED|(+)----(VCC)         // pin on PCF8574; cathode; resistor >= 330 Om
#define BUTTON_PIN 1 // (VCC)--[R 10 kOm]--(PCF8574 (1))----|BUTTON|----(GND)   //pin on PCF8574; pullup (10kOm to VCC)

Max_PCF8574 expander;

void setup() {
  expander.begin(PCF8574_ADDRESS);

  expander.setBitMode(LED_PIN, OUTPUT_BIT);
  expander.setBitMode(BUTTON_PIN, INPUT_BIT);
//  expander.setBitModeMask(0b01000000); // INPUT_BIT = 1; OUTPUT_BIT = 0;
}

void loop() {
  byte bitValue = expander.getBit(BUTTON_PIN);
  
  if(bitValue == 0) {
    expander.setBit(LED_PIN, LOW);
  }
  else {
    expander.setBit(LED_PIN, HIGH);
  }


//  byte byteValue = expander.getByte();
//  expander.setByte(0b00000000);
}
