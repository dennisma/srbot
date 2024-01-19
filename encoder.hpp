
#ifndef __ENCODER_HPP__
#define __ENCODER_HPP__
#include "pins.hpp"

namespace srbots{
	/// \brief Encoder acts as an encoder value attached to two quadature encoder pins (enc1A and enc1B )
	class Encoder {
	public:
	  /// \brief Encoder acts as an encoder value attached to two quadature encoder pins
	  Encoder();
	  /// \brief init will initialize the encoders and set the pinds
	  /// \param  a - signal A pin - this will have the interrupt on it -  defaults to enc1A
	  /// \param  b - signal B pin - this will have the interrupt on it -  defaults to enc1B
	  void init(int a=enc1A,int b=enc1B);
	  /// \brief internalInit MUST be called on setup1() to work on second core
	  void internalInit();  
	  /// \brief reset encoder count to 0
	  void reset();
	  /// \brief get encoder count
	  int_fast32_t count();
	};

	extern Encoder enc;
}
#endif