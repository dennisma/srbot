#include <stdio.h>
#include "pins.hpp"
#include <iostream>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "MyI2CInitStuff.hpp"

namespace srbots {

void i2cbus::init() {	
	if (!initialized) initialized = true;
	else return;

	i2c_init(_i2cport, _bus_speed);
	gpio_set_function(_sda_pin, GPIO_FUNC_I2C);
	gpio_set_function(_scl_pin, GPIO_FUNC_I2C);

	gpio_pull_up(_sda_pin);
	gpio_pull_up(_scl_pin);
}

void i2cbus::deinit(bool full) {
	initialized = false;
	i2c_deinit(_i2cport);
	if (full) {
		gpio_disable_pulls(_sda_pin);
		gpio_disable_pulls(_scl_pin);
	}
}

void i2cbus::i2cbuff(I2CBUFF buf, uint8_t first,uint8_t second,uint8_t third,uint8_t fourth,uint8_t fifth,uint8_t sixth){
    memset(buf.buf,0,buf.sz);
    if (buf.sz >= 6){
        buf.buf[0] = first;
        buf.buf[1] = second;
        buf.buf[2] = third;
        buf.buf[3] = fourth;
        buf.buf[4] = fifth;
        buf.buf[5] = sixth;
    }
} 
int i2cbus::Write(I2CBUFF buf,uint8_t _addr, uint16_t numbytes){
    volatile auto err = i2c_write_blocking(_i2cport, _addr, buf.buf, numbytes, false);
    return err;
}

int i2cbus::Read(I2CBUFF buf, uint8_t _addr, uint16_t numbytes){
    i2cbuff(buf);
    return i2c_read_blocking(_i2cport,_addr,buf.buf,numbytes,false);
}

//---------------------------------------------------------------------------------------------

void I2CSensor::i2cbuff(I2CBUFF buf, uint8_t first,uint8_t second,uint8_t third,uint8_t fourth,uint8_t fifth,uint8_t sixth){
    _i2cbus->i2cbuff(buf,first,second,third,fourth,fifth,sixth);
} 
int I2CSensor::Write(I2CBUFF buf, uint16_t numbytes){
    return _i2cbus->Write(buf,_addr,numbytes);
}

int I2CSensor::Read(I2CBUFF buf, uint16_t numbytes){
    i2cbuff(buf);
    return _i2cbus->Read(buf,_addr,numbytes);
}

int I2CSensor::WriteRead(I2CBUFF buf, uint16_t numbytesWrite, uint16_t numbytesRead){
    int err = Write(buf,numbytesWrite);
    if (err == PICO_ERROR_GENERIC) return err;
    return Read(buf,numbytesRead);
}

/// @brief Represents i2c0
i2cbus i2cport0(i2c0, I2C_SDA0, I2C_SCL0, 400 * 1000);
/// @brief Represents i2c1
i2cbus i2cport1(i2c1, I2C_SDA1, I2C_SCL1, 400 * 1000);
};