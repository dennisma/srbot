#ifndef __CYTRON_BUTT_HPP__
#define __CYTRON_BUTT_HPP__
#include <Arduino.h>
#include "hardware/gpio.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
namespace srbots{
	/// @brief Class Button represents a button either on the cytron board or one that is 
	// on a breadboard.  Detects button presses even if blocked (ex:  delay(9000);)
	class Button {
	private:
	  uint8_t _pin;
	  gpio_irq_level _event;
	  PinMode _mode;
	public:
	/**
	* constructor takes a pin number and the optional event and pinmode that comprises a button press
	* @param pin an integer argument.
	* @param event the event to capture - Can be GPIO_IRQ_EDGE_FALL or GPIO_IRQ_EDGE_RISE
	* @param mode For on board buttons (GP20 and GP21) just use default of INPUT.  Can be any pinMode though
	*/
	  explicit Button(const uint8_t pin, gpio_irq_level event=GPIO_IRQ_EDGE_FALL,PinMode mode=INPUT);
	  Button() = delete;

	/**
	* initializes the button (call from setup() )
	* @see setup()
	*/
	  void init();

	/**
	* returns true if the button attached to the pin was pressed
	* @return True if button was ever pushed
	*/
	  bool pressed();
	  // clears the button event (pressed() method calls this automatically)
	/**
	* resets the button pressed flag to false. Automatically called by pressed()
	*/
	  void clear();
	};
};

#endif