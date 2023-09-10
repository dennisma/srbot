enum Direction {FORWARD,REVERSE};


namespace srbots{
struct CytronMotor {
  uint8_t slice;
  uint8_t chan;
  uint8_t m_pwmfpin;
  uint8_t m_pwmrpin;
  Direction dir;
  uint16_t  wrap;

  CytronMotor(const uint8_t slice, const uint8_t chan, const uint8_t m_pwmfpin, const uint8_t m_pwmrpin,
    const Direction dir, const uint16_t wrap);

  // speedval = can be between -100 and 100 percent
  void speed(double speedval);
};
};
extern  srbots::CytronMotor &leftmotor;// = motors[0];
extern  srbots::CytronMotor &rightmotor;// = motors[1];