#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include "hardware/i2c.h"
#include "MyI2CInitStuff.hpp"
#include "tcs34725.hpp"

//constexpr uint8_t tcsaddr = 0x29;
namespace srbots {
constexpr uint8_t tcsID   = 0xAB;
constexpr uint8_t memCOLORADDR = 0x94;
#define BUF_SIZE 17
bool ColorDetector::tcsgetID(){
    uint8_t txdata[BUF_SIZE];
    I2CBUFF buf ={txdata,BUF_SIZE};
    i2cbuff(buf,0x92);
    auto err = Write(buf,1);
    uint8_t count = 5;
    while (err == PICO_ERROR_GENERIC && count--){
        sleep_ms(2);
        i2cbuff(buf,0x00);
        err = Write(buf,1);
    }
    if (err == PICO_ERROR_GENERIC) return false;
    err = Read(buf, 1);
    if (err == PICO_ERROR_GENERIC) return false;
    if (txdata[0] != tcsID) return false;
    return true;
}
bool ColorDetector::init(uint16_t iTimeMS){
	if (!init()) return false;
	return setADCIntegrationTime(iTimeMS);
}
bool ColorDetector::init() {
    uint8_t txdata[BUF_SIZE];
    I2CBUFF buf ={txdata,BUF_SIZE};
    sleep_ms(100);
    int err = 0;

    if (!tcsgetID()) return false;
	if (!setADCIntegrationTime(10)) return false;

	// send lots of data
	{
		twovals tosend[] = { 
			{0x8F, 0x02},    // 0x02 is 16x gain, 0x01 is 4x gain
			{0xAB, 0x00}, 
			{0x80, 0x00}, 
			{0x80, 0x00}, 
			{0x80, 0x00}, 
			{0x80, 0x00}, 
			{0x80, 0x00} 
		};

		for (auto[f,s] : tosend){
			i2cbuff(buf,f,s);
			err = Write(buf,2);
			if (err == PICO_ERROR_GENERIC) return false;   
		}
	}
	
	{
		i2cbuff(buf,0xE7);
		err = Write(buf,1);
			if (err == PICO_ERROR_GENERIC) return false; 
	
	}
	
	{
		twovals tosend[] = {
			{0x80, 0x00}
		};

		for (auto[f,s] : tosend){
			i2cbuff(buf,f,s);
			err = Write(buf,2);
			if (err == PICO_ERROR_GENERIC) return false;   
		}
	}
	
	delay(10);
	{
		twovals tosend[] = {
			{0x80, 0x01}
		};

		for (auto[f,s] : tosend){
			i2cbuff(buf,f,s);
			err = Write(buf,2);
			if (err == PICO_ERROR_GENERIC) return false;   
		}
	}
	
	delay(10);

	{
		twovals tosend[] = {
			{0xAA, 0x00}, 
			{0xA2, 0x40}, 
			{0xA3, 0x40}, 
			{0xA0, 0x32}, 
			{0xA6, 0xC9}
		};

		for (auto[f,s] : tosend){
			i2cbuff(buf,f,s);
			err = Write(buf,2);
			if (err == PICO_ERROR_GENERIC) return false;   
		}
	}	
	delay(10);
	{
		twovals tosend[] = {
			{0x80, 0x03}//enable color!!!
		};

		for (auto[f,s] : tosend){
			i2cbuff(buf,f,s);
			err = Write(buf,2);
			if (err == PICO_ERROR_GENERIC) return false;   
		}
	}

    return true;		
}


bool ColorDetector::colorReady(){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};
    i2cbuff(buf,0x93);
    auto err = WriteRead(buf,1,1);
    if (err == PICO_ERROR_GENERIC) return false;
	return buffer[0] & 0x01;
}

bool ColorDetector::getColors(uint16_t& red, uint16_t& green, uint16_t& blue) {
    uint16_t clear;
    return getColors(red, green,  blue, clear);
}

bool ColorDetector::getColors(uint16_t& red, uint16_t& green, uint16_t& blue,uint16_t& clear) {
    red = blue = green = clear = 0;
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};
    i2cbuff(buf,0x94);
    auto err = WriteRead(buf,1,8);
    if (err == PICO_ERROR_GENERIC) return false;
    // low byte  then high byte
    // clear, read, green, blue

    clear =  ((0xFFFF & buffer[1]) << 8) | buffer[0] ;
    red =    ((0xFFFF & buffer[3]) << 8) | buffer[2] ;
    green =  ((0xFFFF & buffer[5]) << 8) | buffer[4] ;
    blue =   ((0xFFFF & buffer[7]) << 8) | buffer[6] ;

    return true;
}


bool ColorDetector::setADCIntegrationTime(uint16_t iTimeMS) {
  float temp;

  // convert ms into 2.78ms increments
  temp = iTimeMS;
  temp /= 2.78;
  temp = 256 - temp;
  if (temp > 255)
    temp = 255;
  if (temp < 0)
    temp = 0;

    uint8_t txdata[BUF_SIZE];
    I2CBUFF buf ={txdata,BUF_SIZE};
  
	twovals tosend[] = {
		{0x81, (uint8_t)temp}
	};

	for (auto[f,s] : tosend){
		i2cbuff(buf,f,s);
		auto err = Write(buf,2);
		if (err == PICO_ERROR_GENERIC) return false;   
	}
  
	return true;
  
}



};