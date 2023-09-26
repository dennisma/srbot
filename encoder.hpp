
#ifndef __ENCODER_HPP__
#define __ENCODER_HPP__
#include "pins.hpp"

namespace srbots{
	/// \brief Encoder acts as an encoder value attached to two quadature encoder pins (enc1A and enc1B )
	class Encoder {
	public:
	  /// \brief Encoder acts as an encoder value attached to two quadature encoder pins
	  Encoder();
	  /// \brief init MUST be called on setup1() to work on second core
	  void init();  
	  /// \brief reset encoder count to 0
	  void reset();
	  /// \brief get encoder count
	  int_fast32_t count();
	};

	extern Encoder enc;
}
#endif