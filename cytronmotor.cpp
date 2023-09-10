#include <Arduino.h>
//#include <stdio.h>
//#include "pico/stdlib.h"
//#include <iostream>

#include <cmath>

#include "pico/time.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "cytronmotor.h"


void speed_motor(srbots::CytronMotor& m,double speed);
uint32_t init_motor(srbots::CytronMotor& m);
namespace srbots{

struct CytronMotor;


CytronMotor::CytronMotor(const uint8_t slice, const uint8_t chan, const uint8_t m_pwmfpin, const uint8_t m_pwmrpin,
  const Direction dir, const uint16_t wrap)
  : slice(slice),
    chan(chan),
    m_pwmfpin(m_pwmfpin),
    m_pwmrpin(m_pwmrpin),
    dir(dir),
    wrap(wrap)
{
  init_motor(*this);
}

void CytronMotor::speed(double speedval){
  speed_motor(*this, speedval);
}
 
};

using namespace srbots;
CytronMotor motors[] = {
  {0,0,8,9,FORWARD,0},
  {0,0,10,11,FORWARD,0}
};
CytronMotor &leftmotor = motors[0];
CytronMotor &rightmotor = motors[1];

uint32_t init_motor(srbots::CytronMotor& m);
void speed_motor(srbots::CytronMotor& m,double speed);
void direction_motor(srbots::CytronMotor& m,Direction dir);

void testprint(){
    //puts("hey I'm an output!");
}

constexpr double fc_init = 125000000.0;
void calc_best_clock_divider(uint32_t hz, double &fc_new, uint32_t &intpart, uint &fracpart)
{
  /*
      so we need an int part and a frac part for pwm_set_clkdiv_int_frac

      let numerator = ceil(fc_init/(hz * 4096))

      intpart  is numerator / 16
      fracpart is numerator % 16

      Also can calc the new fc (we need this to set wrap)
      fc_new = 16.0 * fc_init/numerator
  */

  double d_hz = double(hz);
  // auto numerator = uint32_t(ceil(fc_init/(d_hz * 4096.0)));
  auto numerator = uint32_t(ceil(fc_init / d_hz / 4096.0));
  intpart = numerator / 16;
  fracpart = numerator % 16;

  fc_new = (16.0 * fc_init) / numerator;
}

uint16_t calc_wrap_point(double fc, uint hz, bool phase_correct = false)
{
  if (!phase_correct)
  {
    return (fc / hz) - 1;
  }
  else
  {
    return (fc / (2 * hz)) - 1;
  }
}

uint32_t pwm_get_wrap(uint slicenum)
{
  valid_params_if(PWM, slicenum >= 0 && slicenum < NUM_PWM_SLICES);
  return pwm_hw->slice[slicenum].top;
}

void pwm_set_duty(uint slicenum, uint chan, int duty)
{
  auto wrap = pwm_get_wrap(slicenum);
  pwm_set_chan_level(slicenum, chan, wrap * duty / 100);
}

uint32_t pwm_set_freq_duty(uint slice, uint chan, uint32_t f, uint32_t d)
{
  // fc_init
  uint32_t clock = fc_init;
  uint32_t divider16 = clock / f / 4096 * +(clock % (f * 4096) != 0);
  if (divider16 / 16 == 0)
    divider16 = 16;

  volatile uint32_t wrap = (clock * 16 / divider16 / f) - 1;
  volatile uint8_t intpart = divider16 / 16;
  volatile uint8_t fracpart = divider16 % 16;
  pwm_set_clkdiv_int_frac(slice,intpart, fracpart);
  pwm_set_wrap(slice, wrap);
  pwm_set_chan_level(slice, chan, wrap * d / 100);

  return wrap;
}

uint32_t init_motor(srbots::CytronMotor& m)
{
  m.dir = FORWARD;

  gpio_set_function(m.m_pwmfpin, GPIO_FUNC_PWM);
  m.slice = pwm_gpio_to_slice_num(m.m_pwmfpin);
  m.chan  = pwm_gpio_to_channel  (m.m_pwmfpin);
  m.wrap  = pwm_set_freq_duty    (m.slice, m.chan, 10000, 0);
  pwm_set_enabled(m.slice, true);

  gpio_set_function(m.m_pwmrpin, GPIO_FUNC_PWM);
  m.slice = pwm_gpio_to_slice_num(m.m_pwmrpin);
  m.chan  = pwm_gpio_to_channel  (m.m_pwmrpin);
  m.wrap  = pwm_set_freq_duty    (m.slice, m.chan, 10000, 0);
  pwm_set_enabled(m.slice, true);

  return m.wrap;
}

void speed_motor(srbots::CytronMotor& m,double speed){
  int drivepin ;
  int sleeppin;

  speed = constrain(speed,-100,100);
  if (speed >=0){
    m.dir = FORWARD;
    drivepin =  m.m_pwmfpin;
    sleeppin = m.m_pwmrpin;
  }
  else{
    m.dir = REVERSE;
    drivepin =  m.m_pwmrpin;
    sleeppin = m.m_pwmfpin;    
  }

  volatile int wrap = pwm_get_wrap(pwm_gpio_to_slice_num(drivepin));

  speed = abs(speed);
  pwm_set_gpio_level(sleeppin, 0);
  pwm_set_gpio_level(drivepin, speed / 100 * double(wrap));
}
