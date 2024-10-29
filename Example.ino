/*
 * Example - SkyTech_PCF8574 Library
 * Created by Patrick NDAYIKUNDA, SkyTech Electronics
 * Date: 13 October 2022
 * License: MIT
 *
 * This example demonstrates basic usage of the SkyTech_PCF8574 library
 * to control input and output pins on the PCF8574 GPIO expander.
 */

#include <SkyTech_PCF8574.h>

// Define the I2C address of the PCF8574 (e.g., 0x20)
SkyTech_PCF8574 pcf(0x20);

void setup() {
    // Initialize I2C communication
    pcf.begin();

    // Configure the pins (P0, P1, P2 as input; P3-P7 as output)
    pcf.configPinsDirection(3);
    
    //pcf.configurePins(); /* This function configure the pins (P0, P1, P2 as input; P3-P7 as output) by default */

}

void loop() {
    // Read each input pin and control corresponding output pins
    if (pcf.readInputPin(0)) {
        pcf.writeOutputPin(3, HIGH);  // Set P3 HIGH if P0 is HIGH
    } else {
        pcf.writeOutputPin(3, LOW);   // Set P3 LOW if P0 is LOW
    }

    if (pcf.readInputPin(1)) {
        pcf.writeOutputPin(4, HIGH);  // Set P4 HIGH if P1 is HIGH
    } else {
        pcf.writeOutputPin(4, LOW);   // Set P4 LOW if P1 is LOW
    }

    if (pcf.readInputPin(2)) {
        pcf.writeOutputPin(5, HIGH);  // Set P5 HIGH if P2 is HIGH
    } else {
        pcf.writeOutputPin(5, LOW);   // Set P5 LOW if P2 is LOW
    }

    // Add a small delay to debounce the input switches
    delay(50);
}

