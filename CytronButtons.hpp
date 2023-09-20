#ifndef __CYTRON_BUTT_HPP__
#define __CYTRON_BUTT_HPP__
#include <Arduino.h>
#include "hardware/gpio.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
namespace srbots{
	// Class Button represents a button either on the cytron board or one that is 
	// on a breadboard.
	class Button {
	private:
	  uint8_t _pin;
	  gpio_irq_level _event;
	  PinMode _mode;
	public:
	  // constructor takes a pin number and the optional event and pinmode that comprises a button press
	  explicit Button(const uint8_t pin, gpio_irq_level event=GPIO_IRQ_EDGE_FALL,PinMode mode=INPUT);
	  Button() = delete;
	  // initializes the button (call from setup()
	  void init();
	  // returns true if the button attached to the pin was pressed
	  bool pressed();
	  // clears the button event (pressed() method calls this automatically)
	  void clear();
	};
};

#endif