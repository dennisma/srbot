#pragma once

#include <Arduino.h>

#define TIMEOUT INT_MAX
#define BARF TIMEOUT

#include "MyI2CInitStuff.hpp"
#include "OLEDDisplay.hpp"
#include "tcs34725.hpp"
#include "Ultrasonic.hpp"
#include "cytronmotor.h"
#include "encoder.hpp"
#include "CytronButtons.hpp"
#include "myutil.hpp"
#include <Adafruit_NeoPXL8.h> // install NeoPXL8 library and ALL DEPENDENCIES!!!!!!!!!!!!!!!

extern Adafruit_NeoPXL8 pixy; 

// this is to make it compatible with the Webots stuff....
#define runsim() 1
extern srbots::Button button20;
extern srbots::Button button21;



namespace srbots {
	/// @brief Initializes some of the global objects used - call this in setup()
	void RobotSetup();
};