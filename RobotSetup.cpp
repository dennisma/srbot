#include "RobotSetup.hpp"
#define NUM_LEDS    2                                 // number of pixels
#define COLOR_ORDER                                   // NeoPixel color format (see Adafruit_NeoPixel)

int8_t neopixel_pins[8] = {  NEO_PIN,-1,-1,-1,-1,-1,-1,-1};    // We only have one "strand" so set others strands to pin -1
Adafruit_NeoPXL8 pixy(NUM_LEDS, neopixel_pins); 

namespace srbots {
	void RobotSetup(){
	  port0->init();
	  port1->init();
	  
	  if (!pixy.begin()) {                                // always check errors!
		Serial.println("Ooops error");
		while(1);
	  }
	  pixy.setBrightness(64);                             // 0 is min (off) and 255 is max
	  pixy.clear();                                       // turn them all off
	  pixy.show();                                        // must call show(), that is when color is sent.

	}
}
