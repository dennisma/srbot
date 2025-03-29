#include <Arduino.h>
#include "MyI2CInitStuff.hpp"    
#include "TOF.hpp"

#define BUF_SIZE 17
namespace srbots {

bool TOF::init(){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    wr(0xC0 );
    //read to 0x29 ack data: 0xEE
    wr(0x89 );
    //read to 0x29 ack data: 0x00

    w( 0x89 ,0x01 );
    w( 0x88 ,0x00 );
    w( 0x80 ,0x01 );
    w( 0xFF ,0x01 );
    w( 0x00 ,0x00 );
    wr(0x91 );
    //read to 0x29 ack data: 0x3C
    w( 0x00 ,0x01 );
    w( 0xFF ,0x00 );
    w( 0x80 ,0x00 );
    wr(0x60 );
    //read to 0x29 ack data: 0x00
    w( 0x60 ,0x12 );
    w( 0x44 ,0x00 ,0x20 );

    w( 0x01 ,0xFF );
    w( 0x80 ,0x01 );
    w( 0xFF ,0x01 );
    w( 0x00 ,0x00 );
    w( 0xFF ,0x06 );
    wr(0x83 );
    //read to 0x29 ack data: 0x01
    w( 0x83 ,0xDD );
    w( 0xFF ,0x07 );
    w( 0x81 ,0x01 );
    w( 0x80 ,0x01 );
    w( 0x94 ,0x6B );
    w( 0x83 ,0x00 );
   //wr(0x83 );
    if (!check83()) return false;
    //read to 0x29 ack data: 0x10
    w( 0x83 ,0x01 );
    wr(0x92 );
    //read to 0x29 ack data: 0x05
    w( 0x81 ,0x00 );
    w( 0xFF ,0x06 );
    wr(0x83 );
    //read to 0x29 ack data: 0x05
    w( 0x83 ,0xD9 );
    w( 0xFF ,0x01 );
    w( 0x00 ,0x01 );
    w( 0xFF ,0x00 );
    w( 0x80 ,0x00 );

    wr(0xB0,6); 
    //read to 0x29 ack data: 0xFB 0xFF 0xEF 0xEF 0x7E 0x0F

    w( 0xFF ,0x01 );
    w( 0x4F ,0x00 );
    w( 0x4E ,0x2C );
    w( 0xFF ,0x00 );
    w( 0xB6 ,0xB4 );
    w(0xB0 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 );
    w( 0xFF ,0x01 );
    w( 0x00 ,0x00 );
    w( 0xFF ,0x00 );
    w( 0x09 ,0x00 );
    w( 0x10 ,0x00 );
    w( 0x11 ,0x00 );
    w( 0x24 ,0x01 );
    w( 0x25 ,0xFF );
    w( 0x75 ,0x00 );
    w( 0xFF ,0x01 );
    w( 0x4E ,0x2C );
    w( 0x48 ,0x00 );
    w( 0x30 ,0x20 );
    w( 0xFF ,0x00 );
    w( 0x30 ,0x09 );
    w( 0x54 ,0x00 );
    w( 0x31 ,0x04 );
    w( 0x32 ,0x03 );
    w( 0x40 ,0x83 );
    w( 0x46 ,0x25 );
    w( 0x60 ,0x00 );
    w( 0x27 ,0x00 );
    w( 0x50 ,0x06 );
    w( 0x51 ,0x00 );
    w( 0x52 ,0x96 );
    w( 0x56 ,0x08 );
    w( 0x57 ,0x30 );
    w( 0x61 ,0x00 );
    w( 0x62 ,0x00 );
    w( 0x64 ,0x00 );
    w( 0x65 ,0x00 );
    w( 0x66 ,0xA0 );
    w( 0xFF ,0x01 );
    w( 0x22 ,0x32 );
    w( 0x47 ,0x14 );
    w( 0x49 ,0xFF );
    w( 0x4A ,0x00 );
    w( 0xFF ,0x00 );
    w( 0x7A ,0x0A );
    w( 0x7B ,0x00 );
    w( 0x78 ,0x21 );
    w( 0xFF ,0x01 );
    w( 0x23 ,0x34 );
    w( 0x42 ,0x00 );
    w( 0x44 ,0xFF );
    w( 0x45 ,0x26 );
    w( 0x46 ,0x05 );
    w( 0x40 ,0x40 );
    w( 0x0E ,0x06 );
    w( 0x20 ,0x1A );
    w( 0x43 ,0x40 );
    w( 0xFF ,0x00 );
    w( 0x34 ,0x03 );
    w( 0x35 ,0x44 );
    w( 0xFF ,0x01 );
    w( 0x31 ,0x04 );
    w( 0x4B ,0x09 );
    w( 0x4C ,0x05 );
    w( 0x4D ,0x04 );
    w( 0xFF ,0x00 );
    w( 0x44 ,0x00 );
    w( 0x45 ,0x20 );
    w( 0x47 ,0x08 );
    w( 0x48 ,0x28 );
    w( 0x67 ,0x00 );
    w( 0x70 ,0x04 );
    w( 0x71 ,0x01 );
    w( 0x72 ,0xFE );
    w( 0x76 ,0x00 );
    w( 0x77 ,0x00 );
    w( 0xFF ,0x01 );
    w( 0x0D ,0x01 );
    w( 0xFF ,0x00 );
    w( 0x80 ,0x01 );
    w( 0x01 ,0xF8 );
    w( 0xFF ,0x01 );
    w( 0x8E ,0x01 );
    w( 0x00 ,0x01 );
    w( 0xFF ,0x00 );
    w( 0x80 ,0x00 );
    w( 0x0A ,0x04 );
    wr(0x84 );
    //read to 0x29 ack data: 0x01
    w( 0x84 ,0x01 );
    w( 0x0B ,0x01 );
    wr(0x01 );
    //read to 0x29 ack data: 0xF8
    wr(0x50 );
    //read to 0x29 ack data: 0x06
    wr(0x46 );
    //read to 0x29 ack data: 0x25
    wr(0x51,2 );
    //read to 0x29 ack data: 0x00 0x96
    wr(0x70 );
    //read to 0x29 ack data: 0x04
    wr(0x71,2 );
    //read to 0x29 ack data: 0x01 0xFE
    w( 0x01 ,0xE8 );
    wr(0x01 );
    //read to 0x29 ack data: 0xE8
    wr(0x50 );
    //read to 0x29 ack data: 0x06
    wr(0x46 );
    //read to 0x29 ack data: 0x25
    wr(0x51,2 );
    //read to 0x29 ack data: 0x00 0x96
    wr(0x70 );
    //read to 0x29 ack data: 0x04
    wr(0x71 ,2);
    //read to 0x29 ack data: 0x01 0xFE
    w(0x71, 0x02, 0x90); 
    w( 0x01 ,0x01 );
    w( 0x00 ,0x41 );

    if (!check13()) return false;

    w( 0x0B ,0x01 );
    w( 0x00 ,0x00 );
    w( 0x01 ,0x02 );
    w( 0x00 ,0x01 );

    if (!check13()) return false;

    w( 0x0B ,0x01 );
    w( 0x00 ,0x00 );
    w( 0x01 ,0xE8 );
    return setContinuous();
}

bool TOF::setContinuous(){
    w(0x80 ,0x01 );
    w(0xFF ,0x01 );
    w(0x00 ,0x00 );
    w(0x91 ,0x3C );
    w(0x00 ,0x01 );
    w(0xFF ,0x00 );
    w(0x80 ,0x00 );
    w(0x00 ,0x02 );
    return true;
}

int TOF::getDistanceMM(){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};
    // write to 0x29 ack data: 0x13 
    // read to 0x29 ack data: 0x44
    // write to 0x29 ack data: 0x1E 
    // read to 0x29 ack data: 0x01 0xDA       // the value
    // write to 0x29 ack data: 0x0B 0x01 
    if (!check13()) return TIMEOUT;
    i2cbuff(buf,0x1E);
    auto err = WriteRead(buf,1,2);
    if (err == PICO_ERROR_GENERIC) return TIMEOUT;
    int ret = (buf.buf[0] << 8) | buf.buf[1];
    w(0x0B ,0x01 );
    //Serial.println(ret);
    return ret;
} 
bool TOF::check13(){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};
    int count = 0;
    while (true){
        i2cbuff(buf,0x13);
        auto err = WriteRead(buf,1,1);
        if (err == PICO_ERROR_GENERIC) return false;
        if (buf.buf[0] & 0x07){
            return true;
        }  
        delay(10);
    }
    return false;
}
bool TOF::check83(){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};
    int count = 0;
    while (true){
        i2cbuff(buf,0x83);
        auto err = WriteRead(buf,1,1);
        if (err == PICO_ERROR_GENERIC) return false;
        if (buf.buf[0] != 0x00){
            return true;
        }  
        delay(10);
    }
    return false;
}


bool TOF::wr(uint8_t val,int readbytes){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val);
    auto err = WriteRead(buf,1,readbytes);
    return (err != PICO_ERROR_GENERIC);
    //return true;
}
bool TOF::w(uint8_t val){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val);
    auto err = Write(buf,1);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;  
}
bool TOF::w(uint8_t val,uint8_t val2){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val,val2);
    auto err = Write(buf,2);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
bool TOF::w(uint8_t val,uint8_t val2,uint8_t val3){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val,val2,val3);
    auto err = Write(buf,3);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
bool TOF::w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val,val2,val3,val4);
    auto err = Write(buf,4);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
bool TOF::w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val,val2,val3,val4,val5);
    auto err = Write(buf,5);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
bool TOF::w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5,uint8_t val6){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    i2cbuff(buf,val,val2,val3,val4,val5,val6);
    auto err = Write(buf,6);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
bool TOF::w(uint8_t val,uint8_t val2,uint8_t val3,uint8_t val4,uint8_t val5,uint8_t val6, uint8_t val7){
    uint8_t buffer[BUF_SIZE];
    I2CBUFF buf ={buffer,BUF_SIZE};

    //i2cbuff(buf,val,val2,val3,val4,val5,val6,val7);
    memset(buf.buf,0,buf.sz);
    auto err = Write(buf,7);
    if (err == PICO_ERROR_GENERIC) return false; 
    return true;
}
};