
#ifndef __ENCODER_HPP__
#define __ENCODER_HPP__
#include "pins.hpp"


class Encoder {
public:
  Encoder();
  void init();  // must be called on setup1() to work on second core
  // reset encoder count to 0
  void reset();
  // get encoder count
  int_fast32_t count();
};


extern Encoder enc;

#endif