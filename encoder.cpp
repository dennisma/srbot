#include <Arduino.h>
#include "encoder.hpp"

volatile int_fast32_t encCount = 0;

int __encoder_a = enc1A;
int __encoder_b = enc1B;

namespace srbots{
	
	void encodercallback() {
	  auto pins = sio_hw->	gpio_in;

	  if (pins & (1 << ::__encoder_a))
		(pins & (1 << ::__encoder_b)) ? encCount-- : encCount++;
	  else
		(pins & (1 << ::__encoder_b)) ? encCount++ : encCount--;
	}


	Encoder::Encoder() {
	}

	void Encoder::init(int a,int b){
        rp2040.fifo.push(a);
        rp2040.fifo.push(b);
	}

	void Encoder::internalInit() {
	  Serial.println("Enc Init");
	  pinMode(::__encoder_a, INPUT);
	  pinMode(::__encoder_b, INPUT);
	  void (*func)() = encodercallback;
	  Serial.println("encoder pins\n");
	  	Serial.println(__encoder_a);
		Serial.println(__encoder_b);
	  //attachInterrupt(digitalPinToInterrupt(::__encoder_a), func, CHANGE);
	  attachInterrupt(digitalPinToInterrupt(::__encoder_a), func, RISING);
	}


	void Encoder::reset() {
	  encCount = 0;
	}


	int_fast32_t Encoder::count() {return encCount; }

	Encoder enc;


}

void setup1() {
  __encoder_a = rp2040.fifo.pop();
  __encoder_b = rp2040.fifo.pop();
  Serial.println("Enc Init");
  srbots::enc.internalInit();
}

void loop1() {
	//delay(10000);
}