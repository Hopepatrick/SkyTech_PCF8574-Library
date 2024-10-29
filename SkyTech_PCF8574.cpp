/*
 * SkyTech_PCF8574.cpp - Implementation for PCF8574 I2C GPIO Expander Library
 * Created by Patrick NDAYIKUNDA, SkyTech Electronics
 * Date: 13 October 2022
 * License: MIT
 *
 * This file implements the functions defined in SkyTech_PCF8574.h for controlling
 * the PCF8574 I2C GPIO Expander.
 */

#include "SkyTech_PCF8574.h"
#include <Wire.h>  // Use Wire library only in CPP file

// Constructor to initialize with the I2C address
SkyTech_PCF8574::SkyTech_PCF8574(uint8_t address) : _address(address) {}

void SkyTech_PCF8574::begin() {
    Wire.begin();  // Initialize I2C
}

void SkyTech_PCF8574::configurePins() {
       Wire.beginTransmission(_address);
    Wire.write(0b11100000);  // Configure P0, P1, P2 as input; P3-P7 as output
    Wire.endTransmission();
}
void SkyTech_PCF8574::configPinsDirection(uint8_t numInputs){
// Ensure numInputs is between 1 and 8
    if (numInputs > 8) numInputs = 8;
    else if (numInputs < 1) numInputs = 1;

    // Create a mask with the specified number of MSBs set to 1
    byte configMask = ((1 << numInputs) - 1) << (8 - numInputs);

    // Write the configuration mask to the PCF8574 to set the pins
    Wire.beginTransmission(_address);
    Wire.write(configMask);  // Send the mask to configure pins
    Wire.endTransmission();	
}


byte SkyTech_PCF8574::readInputs() {
    Wire.requestFrom(_address, 1);  // Request 1 byte from PCF8574
    if (Wire.available()) {
        return Wire.read();  // Return the byte received
    }
    return 0;  // Default return value if no data is received
}

bool SkyTech_PCF8574::readInputPin(uint8_t pin) {
    if (pin > 7) return false;  // Only P0, P1, and P2 are inputs
    byte pinStates = readInputs();
    return (pinStates & (1 << pin)) != 0;  // Return the state of the specified pin
}

void SkyTech_PCF8574::writeOutputs(byte outputStates) {
    byte data = (outputStates & 0b11111000) | 0b00000111;  // Preserve input states for P0-P2
    Wire.beginTransmission(_address);
    Wire.write(data);
    Wire.endTransmission();
}

void SkyTech_PCF8574::writeOutputPin(uint8_t pin, bool state) {
    if (pin > 7) return; 

    byte currentStates = readInputs();  // Read current output states
    if (state) {
        currentStates |= (1 << pin);   // Set the pin HIGH
    } else {
        currentStates &= ~(1 << pin);  // Set the pin LOW
    }

    writeOutputs(currentStates);  // Write the updated output state back to PCF8574
}

