enum Direction {FORWARD,REVERSE};


namespace srbots{
/// @brief Class CytronMotor represents a motor on the cytron board  
	struct CytronMotor {
	  uint8_t slice;
	  uint8_t chan;
	  uint8_t m_pwmfpin;
	  uint8_t m_pwmrpin;
	  Direction dir;
	  uint16_t  wrap;

	/**
	* Constructor - takes as arguments
	* @param slice 
	* @param chan 
	* @param m_pwmfpin is the pin that utilizes PWM when driving FORWARD
	* @param m_pwmrpin is the pin that utilizes PWM when driving in REVERSE
	* @param dir - the default direction
	* @param wrap - wrap point for the PWM signal
	*/
	  CytronMotor(const uint8_t slice, const uint8_t chan, const uint8_t m_pwmfpin, const uint8_t m_pwmrpin,
		const Direction dir, const uint16_t wrap);

	/**
	* speed takes a number between -100 and 100 and runs the motor at that percentage.
	* @param speedval = can be between -100 and 100 percent
	*/
	  void speed(double speedval);
	};
};
extern  srbots::CytronMotor &leftmotor;// = motors[0];
extern  srbots::CytronMotor &rightmotor;// = motors[1];