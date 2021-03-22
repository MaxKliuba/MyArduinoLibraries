/*
 * ATTiny, Arduino and ESP8266 library to interface with PCF8574
 * install TinyWireM library https://github.com/adafruit/TinyWireM
 * ATTiny85 I2C interface: SDA - pin P0 (0) and SCL - pin 2 (2); pull up to VCC (resistor 10kOm)
 * Arduino Nano I2C interface: SDA - pin A4 and SCL - pin A5
 * ESP8266 I2C interface: SDA - pin GPIO4 and SCL - pin GPIO5
 *
 * by Maxim Kliuba
 */

#pragma once
#include "Arduino.h"

#define Max_PCF8574_h

#define INPUT_BIT 1
#define OUTPUT_BIT 0

class Max_PCF8574 {
	public:
		Max_PCF8574();

		void begin(uint8_t address);
		void setBitMode(uint8_t bit, uint8_t mode);
		void setBitModeMask(uint8_t bitModeMask);
		void setBit(uint8_t bit, bool value);
		void setByte(uint8_t value);
		bool getBit(uint8_t bit);
		uint8_t getByte();

		void pinMode(uint8_t pin, uint8_t mode);
		void digitalWrite(uint8_t pin, bool value);
		void write(uint8_t value);
		bool digitalRead(uint8_t pin);
		uint8_t read();

	private:
		int _address;
		uint8_t _currentByte;
		uint8_t _bitModeMask;

		void i2cWrite(uint8_t value);
		uint8_t i2cRead();
	};