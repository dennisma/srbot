#pragma once
#include <Arduino.h>
#ifndef _MY_UTIL_H_
#define	_MY_UTIL_H_

namespace srbots{
	  /// @brief TimeMe is a utility to time sections of code
	  class TimeMe {
	  private:
		bool _autostart;
		uint64_t _start, _end;
		const uint64_t _cycles_per_second;
	  public:
		/// @brief Constructor
		/// @param autostart - true if you want time me to just time for it's life cycle of the object (very useful)
		TimeMe(bool autostart = false);
		~TimeMe();
		/// @brief Start (or restart) the start time
	    void start();
		/// @brief Stop the timer.
		void stop();
		/// @brief The number of clock cycles between the call to start() and stop() (or since the object was created if autostart)
		uint64_t cycles();
		/// @brief The number of nanoseconds between the call to start() and stop() (or since the object was created if autostart)
		uint64_t nS();
		/// @brief The number of microseconds between the call to start() and stop() (or since the object was created if autostart)
		uint64_t uS();
		/// @brief The number of milliseconds between the call to start() and stop() (or since the object was created if autostart)
		uint64_t milliS();
		/// @brief The number of seconds between the call to start() and stop() (or since the object was created if autostart)
		uint64_t Seconds();
		/// @brief prints time between the call to start() and stop() (or since the object was created if autostart).  Will be called automagically in destructor if autostart in constructor is true.
		void printVals();
	  };
	  
	/// @brief WDTimer is a utility set up the Pico's Watchdog Timer
	class WDTimer {
	public:
		/// @brief initializes the timer with the delay_ms
		/// @param if updateDog() is not called within delay_ms of each other board will reboot
		/// @return true if watchdog rebooted the pico
		bool init(uint32_t delay_ms);
		void updateDog();
	};
	  
	  
	/// @brief acts like arduino map - maps from imin imax to omin omax
	/// @tparam T a numeric types (double, int, etc)
	/// @param x the value to map
	/// @param imin the input min val
	/// @param imax the input max val 
	/// @param omin the output min value
	/// @param omax the output max value
	/// @return the mapped value of x
	template <typename T>
	T mapfunc(T x, T imin, T imax, T omin, T omax)
	{
	  return (x - imin) * (omax - omin) / (imax - imin) + omin;
	}

	/// @brief constrains a value between a min and max
	/// @tparam T a numeric type
	/// @param val the value to constrain
	/// @param min the minimum constraint 
	/// @param max the maxiumum constraint
	/// @return if val > max, return max.  if val < min, return min.  Otherwise return val
	template <typename T>
	T constrain_t(T val, T min, T max)
	{
	  if (val < min)
		return min;
	  if (val > max)
		return max;
	  return val;
	}

	/// @brief combo of both constrain and map 
	/// @tparam T a numeric type
	/// @param x the value to mape
	/// @param imin the input min val
	/// @param imax the input max val 
	/// @param omin the output min value
	/// @param omax the output max value
	/// @return the mapped value of x but constrained between omin and omax
	template <typename T>
	T cmap(T x, T imin, T imax, T omin, T omax)
	{
	  return constrain_t(mapfunc(x, imin, imax, omin, omax),
					   omin,
					   omax);
	}
};
#endif