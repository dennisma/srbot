#ifndef _CRAZY_PINS_HPP
#define _CRAZY_PINS_HPP 1

namespace srbots {

//i2c pins
#define I2C_SDA0 0
#define I2C_SCL0 1
#define I2C_SDA1 2
#define I2C_SCL1 3

// motor pins (cytron board)
#define M1FPWM 8
#define M1RPWM 9
#define M2FPWM 10
#define M2RPWM 11

//Ultrasonic
#define TRIGGERPIN  17
#define ECHOPIN     16


#define NUM_LEDS    2                                 // number of pixels
#define COLOR_ORDER                                   // NeoPixel color format (see Adafruit_NeoPixel)
#define NEO_PIN 18                                    // On the Cytron RP2040 the two NEOPIXELS are on pin 18

#define enc1A 26                                      // encoder 
#define enc1B 27

constexpr int lightarraypins[5] = {7,26,15,27,28};
};
#endif