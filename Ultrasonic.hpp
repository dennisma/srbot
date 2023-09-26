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
	void fire();
	
public:
	/// \brief Constructor that sets trigger pin, echo pin, and timeout
	/// \param trigger_pin for the sensor (note pinMode will be set in init)
	/// \param echo_pin for this sensor (note pinMode will be set in init)
	/// \param timeout for the sensor (this appears to not be in any standard measure)
	UltraSonic(uint8_t trigger_pin=TRIGGERPIN, uint8_t echo_pin=ECHOPIN, unsigned long timeout=1160)
		: _trigger_pin(trigger_pin),
		  _echo_pin(echo_pin),
		  _timeout(timeout)
		  {}

	/// \brief Initializes Ultrasonic trigger and echo pins to OUTPUT and INPUT accordingly
	/// \returns True if succesful
	bool init();

	/// \brief Gets distance in centimeters(cm)
	/// \param distance set to be distance but ONLY if get returns True. Invalid is 255
	/// \returns True - distance will be valid - otherwise we timed out.
	bool get(int32_t& distance);
	
	/// \brief Sets timeoput for ping sensor wait
	/// \param timeout for the sensor (this appears to not be in any standard measure)
	void setTimeout(long timeout){_timeout =  timeout;}
	
	/// \brief gets the trigger pin set up for the ultrasonic
	/// \returns trigger pin number
	[[nodiscard]] uint8_t trigger_pin() const { return _trigger_pin; }
	
	/// \brief gets the echo pin set up for the ultrasonic
	/// \returns echo pin number
	[[nodiscard]] uint8_t echo_pin() const { return _echo_pin; }
};
};
#endif
