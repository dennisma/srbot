#include <Arduino.h>
#include "Ultrasonic.hpp"

namespace srbots{
bool UltraSonic::init() {
    gpio_init(_trigger_pin);
    gpio_set_dir(_trigger_pin, GPIO_OUT);

    gpio_set_function(_echo_pin,GPIO_FUNC_SIO);
    gpio_set_dir(_echo_pin,GPIO_IN);
    gpio_pull_down(_echo_pin);

    return true;
}
void UltraSonic::fire() {
    gpio_put(_trigger_pin,0);
    sleep_us(5);
    gpio_put(_trigger_pin,1);
    sleep_us(11);
    gpio_put(_trigger_pin,0);
}
bool UltraSonic::get(int64_t& distance) {
  fire();
  auto t = pulseIn(_echo_pin,HIGH,20l*290l*2l);

  distance = ((t/29)/2);
  
  if (distance == 0) distance = 255;
  return distance !=0;
}
};