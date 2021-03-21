#include "Max_PCF8574.h"

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
	#define TINY_WIRE
	#include <TinyWireM.h>
#else
	#define WIRE
	#include <Wire.h>
#endif


Max_PCF8574::Max_PCF8574() {
	_address = 0;
	_bitModeMask = B11111111;
} 


void Max_PCF8574::begin(uint8_t address) {
	_address = address;
	#if defined (TINY_WIRE)
		TinyWireM.begin();
	#else
		Wire.begin();
	#endif
}


void Max_PCF8574::setBitMode(uint8_t bit, uint8_t mode) {
	if (bit < 0 || bit > 7) {
		return;
	}

	switch (mode) {
		case INPUT_BIT:
			_bitModeMask |= (1 << bit);
			break;
		case OUTPUT_BIT:
			_bitModeMask &= ~(1 << bit);
			break;
	}
}


void Max_PCF8574::setBitModeMask(uint8_t bitModeMask) {
	_bitModeMask = bitModeMask;
}


void Max_PCF8574::setBit(uint8_t bit, bool value) {
	if (bit < 0 || bit > 7) {
		return;
	}

	if (value) {
		setByte(_currentByte | (1 << bit));
	} 
	else {
		setByte(_currentByte & ~(1 << bit));
	}
}


void Max_PCF8574::setByte(uint8_t value) {
	if (_address == 0) {
		return;
	}

	_currentByte = value | _bitModeMask;
	i2cWrite(_currentByte);
}


uint8_t Max_PCF8574::getByte() {
	return i2cRead();
}


bool Max_PCF8574::getBit(uint8_t bit) {
	if (bit < 0 || bit > 7) {
		return 0;
	}

	uint8_t byteValue = getByte();

	return (byteValue & (1<<bit)) != 0;
}


void Max_PCF8574::i2cWrite(uint8_t value) {
	#if defined (TINY_WIRE)
		TinyWireM.beginTransmission(_address);
		TinyWireM.write(value);
		TinyWireM.endTransmission();
	#else
		Wire.beginTransmission(_address);
		Wire.write(value);
		Wire.endTransmission();
	#endif
}


uint8_t Max_PCF8574::i2cRead() {
	#if defined (TINY_WIRE)
		TinyWireM.requestFrom(_address, 1);
		return TinyWireM.read();
	#else
		Wire.requestFrom(_address, 1);
		return Wire.read();
	#endif
}