#include <Arduino.h>
#include "CytronButtons.hpp"


namespace srbots{
uint32_t gpio_get_events(uint gpio) {
#ifdef io_bank0_hw
#define iobank io_bank0_hw
#else
#define iobank iobank0_hw
#endif
  int32_t mask = 0xF << 4 * (gpio % 8);
  return (iobank->intr[gpio / 8] & mask) >> 4 * (gpio % 8);
}
void gpio_clear_events(uint gpio, gpio_irq_level events) {
  gpio_acknowledge_irq(gpio, events);
}

Button::Button(const uint8_t pin,const  gpio_irq_level event, PinMode mode)
  : _pin(pin), _event(event) , _mode(mode)
  {
}

void Button::init() {
  pinMode(_pin, _mode);
  clear();
}

bool Button::pressed() {
  auto events = gpio_get_events(_pin);
  if ((events & _event) != 0) clear();
  return ((events & _event) != 0);
}

void Button::clear() {
  gpio_clear_events(_pin, _event);
}
void Button::waitUntilPressed() {
  while(!pressed());
}
};