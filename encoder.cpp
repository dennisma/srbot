#include <Arduino.h>
#include "encoder.hpp"

volatile int_fast32_t encCount = 0;

template<uint8_t A, uint8_t B>
void encodercallback() {
  auto pins = sio_hw->gpio_in;

  if (pins & (1 << A))
    (pins & (1 << B)) ? encCount-- : encCount++;
  else
    (pins & (1 << B)) ? encCount++ : encCount--;
}


Encoder::Encoder() {
}


void Encoder::init() {
  pinMode(enc1A, INPUT);
  pinMode(enc1B, INPUT);
  void (*func)() = encodercallback<enc1A, enc1B>;
  attachInterrupt(digitalPinToInterrupt(enc1A), func, CHANGE);
}


void Encoder::reset() {
  encCount = 0;
}


int_fast32_t Encoder::count() {return encCount; }

Encoder enc;

void setup1() {
  enc.init();
}

void loop1() {

}
