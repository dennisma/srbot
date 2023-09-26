
#include "myutil.hpp"

namespace srbots{
  TimeMe::TimeMe(bool autostart): _cycles_per_second(rp2040.f_cpu()),
                                  _autostart(autostart)
  {
    start();
  }

  TimeMe::~TimeMe()
  {
    if (_autostart) {
      stop();
      printVals();
    }
  }

  void TimeMe::start()
  {
    _start = rp2040.getCycleCount64();
  }

  void TimeMe::stop()
 {
    _end = rp2040.getCycleCount64();
 }
  uint64_t TimeMe::cycles()
  {
    return _end - _start;
  }

  uint64_t TimeMe::nS()
  {
    return (cycles() * 1'000'000'000) / _cycles_per_second;
  }

  uint64_t TimeMe::uS()
  {
    return (cycles() * 1'000'000) / _cycles_per_second;
  }

  uint64_t TimeMe::milliS()
  {
    return (cycles() * 1'000) / _cycles_per_second;
  }

  uint64_t TimeMe::Seconds()
  {
    return cycles() / _cycles_per_second;
  }

  void TimeMe::printVals()
  {
    Serial.printf("%lu seconds\n", Seconds());
    Serial.printf("%lu millis\n", milliS());
    Serial.printf("%lu micros\n", uS());
    Serial.printf("%lu nanos\n", nS());
  }
  
  
  bool WDTimer::init(uint32_t delay_ms)
  {
    auto reason = watchdog_caused_reboot();
    rp2040.wdt_begin(delay_ms);
    return reason;
  }

  void WDTimer::updateDog()
  {
    rp2040.wdt_reset();
  }
  
  
  
};