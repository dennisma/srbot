#ifndef __HCSR04__H
#define __HCSR04__H 

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pins.hpp"
namespace srbots{
/// @brief ultrasonic distance sensor that acts like an HCSR04
class UltraSonic {
private:
	uint8_t _trigger_pin;
	uint8_t _echo_pin;
	unsigned long _timeout;
	
public:
	UltraSonic(uint8_t trigger_pin=TRIGGERPIN, uint8_t echo_pin=ECHOPIN, unsigned long timeout=1160)
		: _trigger_pin(trigger_pin),
		  _echo_pin(echo_pin),
		  _timeout(timeout)
		  {}

	/// \brief Initializes Ultrasonic
	/// \returns True if succesful
	bool init();

	/// \brief Sends Ultrasonic pulse
	void fire();

	/// \brief Gets distance in centimeters(cm)
	///  MUST call fire() first!
	/// \param distance set to be distance but ONLY if get returns True. Invalid is 255
	/// \returns True - distance will be valid - otherwise we timed out.
	bool get(int64_t& distance);
	
	void setTimeout(long timeout){_timeout =  timeout;}

	[[nodiscard]] uint8_t trigger_pin() const { return _trigger_pin; }
	[[nodiscard]] uint8_t echo_pin() const { return _echo_pin; }
};
};
#endif
