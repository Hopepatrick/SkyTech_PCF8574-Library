/*
 * SkyTech_PCF8574.h - Library for PCF8574 I2C GPIO Expander
 * Created by Patrick NDAYIKUNDA, SkyTech Electronics
 * Date: 13 October 2022
 * License: MIT
 *
 * This library provides basic control functions for the PCF8574 I2C GPIO Expander.
 */


#ifndef SKYTECH_PCF8574_H
#define SKYTECH_PCF8574_H

#include <Arduino.h>

class SkyTech_PCF8574 {
public:
    SkyTech_PCF8574(uint8_t address);  // Constructor takes I2C address

    void begin();
    void configurePins();
    void configPinsDirection(uint8_t numInputs);
	byte readInputs();
    bool readInputPin(uint8_t pin);
    void writeOutputs(byte outputStates);
    void writeOutputPin(uint8_t pin, bool state);

private:
    uint8_t _address;  // Stores the I2C address
};

#endif // SKYTECH_PCF8574_H

