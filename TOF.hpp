#pragma once
#include <Arduino.h>
#include "RobotSetup.hpp"
#include "MyI2CInitStuff.hpp"    

namespace srbots {
    constexpr uint8_t tofaddr = 0x29;
    class TOF : public I2CSensor{
        private:
        bool check13();
        bool check83();
        bool wr(uint8_t val,int readbytes=1);
        bool w(uint8_t val);
        bool w(uint8_t val,uint8_t val2);
        bool w(uint8_t val,uint8_t val2,uint8_t val3);
        bool w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4);
        bool w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5);
        bool w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5,uint8_t val6);
        bool w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5,uint8_t val6, uint8_t val7);
        bool setContinuous();

    public:
        TOF(i2cbus* i2cport): I2CSensor(i2cport, tofaddr) {}
        bool init();
        int  getDistance(){return getDistanceMM()/10;}
		int  getDistanceMM();
    };

} // namespace srbots