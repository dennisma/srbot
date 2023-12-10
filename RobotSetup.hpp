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

namespace srbots {
	/// @brief Initializes some of the global objects used - call this in setup()
	void RobotSetup();

};