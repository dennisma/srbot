#include "myutil.hpp"
#include "TextRenderer.h"
#include "ShapeRenderer.h"

namespace srbots {

    void midptellipse(OLEDDisplay *ssd1306,int rx, int ry, int xc, int yc,WriteMode mode);

    OLEDDisplay::OLEDDisplay(i2cbus* i2cport, OLED_ORIENTATION orientation,uint16_t Address, Size size): I2CSensor(i2cport, Address)  {
        // Set class instanced variables
        this->address = Address;
        this->size = size;
        this->_orientation = orientation;

        this->width = 128;

        if (size == Size::W128xH32) {
            this->height = 32;
        } else {
            this->height = 64;
        }

        // // create a frame buffer
        // this->frameBuffer = FrameBuffer();

        // // display is not inverted by default
        // this->inverted = false;

        // // this is a list of setup commands for the display
        // uint8_t setup[] = {
        //         SSD1306_DISPLAY_OFF,
        //         SSD1306_LOWCOLUMN,
        //         SSD1306_HIGHCOLUMN,
        //         SSD1306_STARTLINE,

        //         SSD1306_MEMORYMODE,
        //         SSD1306_MEMORYMODE_HORZONTAL,

        //         SSD1306_CONTRAST,
        //         0xFF,

        //         SSD1306_INVERTED_OFF,

        //         SSD1306_MULTIPLEX,
        //         63,

        //         SSD1306_DISPLAYOFFSET,
        //         0x00,

        //         SSD1306_DISPLAYCLOCKDIV,
        //         0x80,
                
        //         SSD1306_PRECHARGE,
        //         0x22,

        //         SSD1306_COMPINS,
        //         0x12,

        //         SSD1306_VCOMDETECT,
        //         0x40,

        //         SSD1306_CHARGEPUMP,
        //         0x14,

        //         SSD1306_DISPLAYALL_ON_RESUME,
        //         SSD1306_DISPLAY_ON
        // };

        // // send each one of the setup commands
        // for (uint8_t &command: setup) {
        //     this->cmd(command);
        // }

        // // clear the buffer and send it to the display
        // // if not done display shows garbage data
        // this->clear();
        // this->sendBuffer();

    }

    bool OLEDDisplay::init(){
        // create a frame buffer
        this->i2CInst = this->_i2cbus->i2cport();
        this->frameBuffer = FrameBuffer();

        // display is not inverted by default
        this->inverted = false;

        // this is a list of setup commands for the display
        uint8_t setup[] = {
                SSD1306_DISPLAY_OFF,
                SSD1306_LOWCOLUMN,
                SSD1306_HIGHCOLUMN,
                SSD1306_STARTLINE,

                SSD1306_MEMORYMODE,
                SSD1306_MEMORYMODE_HORZONTAL,

                SSD1306_CONTRAST,
                0xFF,

                SSD1306_INVERTED_OFF,

                SSD1306_MULTIPLEX,
                63,

                SSD1306_DISPLAYOFFSET,
                0x00,

                SSD1306_DISPLAYCLOCKDIV,
                0x80,
                
                SSD1306_PRECHARGE,
                0x22,

                SSD1306_COMPINS,
                0x12,

                SSD1306_VCOMDETECT,
                0x40,

                SSD1306_CHARGEPUMP,
                0x14,

                SSD1306_DISPLAYALL_ON_RESUME,
                SSD1306_DISPLAY_ON
        };

        // send each one of the setup commands
        for (uint8_t &command: setup) {
            this->cmd(command);
        }

        // clear the buffer and send it to the display
        // if not done display shows garbage data
        this->clear();
        this->sendBuffer();
        return this->setOrientation(_orientation) != PICO_ERROR_GENERIC;   
    }

    void OLEDDisplay::setPixel(int16_t x, int16_t y, WriteMode mode) {
        // return if position out of bounds
        if ((x < 0) || (x >= this->width) || (y < 0) || (y >= this->height)) return;

        // byte to be used for buffer operation
        uint8_t byte;

        // display with 32 px height requires doubling of set bits, reason to this is explained in readme
        // this shifts 1 to byte based on y coordinate
        // remember that buffer is a one dimension array, so we have to calculate offset from coordinates
        if (size == Size::W128xH32) {
            y = (y << 1) + 1;
            byte = 1 << (y & 7);
            char byte_offset = byte >> 1;
            byte = byte | byte_offset;
        } else {
            byte = 1 << (y & 7);
        }

        // check the write mode and manipulate the frame buffer
        if (mode == WriteMode::ADD) {
            this->frameBuffer.byteOR(x + (y / 8) * this->width, byte);
        } else if (mode == WriteMode::SUBTRACT) {
            this->frameBuffer.byteAND(x + (y / 8) * this->width, ~byte);
        } else if (mode == WriteMode::INVERT) {
            this->frameBuffer.byteXOR(x + (y / 8) * this->width, byte);
        }


    }

    void OLEDDisplay::sendBuffer() {
        this->cmd(SSD1306_PAGEADDR); //Set page address from min to max
        this->cmd(0x00);
        this->cmd(0x07);
        this->cmd(SSD1306_COLUMNADDR); //Set column address from min to max
        this->cmd(0x00);
        this->cmd(127);

        // create a temporary buffer of size of buffer plus 1 byte for startline command aka 0x40
        unsigned char data[FRAMEBUFFER_SIZE + 1];

        data[0] = SSD1306_STARTLINE;

        // copy framebuffer to temporary buffer
        memcpy(data + 1, frameBuffer.get(), FRAMEBUFFER_SIZE);

        // send data to device
        //i2c_write_blocking(this->i2CInst, this->address, data, FRAMEBUFFER_SIZE + 1, false);
        I2CBUFF buf ={data,FRAMEBUFFER_SIZE + 1};
        Write(buf,FRAMEBUFFER_SIZE + 1)   ; 
    }

    void OLEDDisplay::clear() {
        this->frameBuffer.clear();
    }

    int OLEDDisplay::setOrientation(bool orientation) {
        // remap columns and rows scan direction, effectively flipping the image on display
        if (orientation) {
            this->cmd(SSD1306_CLUMN_REMAP_OFF);
            return this->cmd(SSD1306_COM_REMAP_OFF);
        } else {
            this->cmd(SSD1306_CLUMN_REMAP_ON);
            return this->cmd(SSD1306_COM_REMAP_ON);
        }
    }

    void
    OLEDDisplay::addBitmapImage(int16_t anchorX, int16_t anchorY, uint8_t image_width, uint8_t image_height,
                            uint8_t *image,
                            WriteMode mode) {
        uint8_t byte;
        // goes over every single bit in image and sets pixel data on its coordinates
        for (uint8_t y = 0; y < image_height; y++) {
            for (uint8_t x = 0; x < image_width / 8; x++) {
                byte = image[y * (image_width / 8) + x];
                for (uint8_t z = 0; z < 8; z++) {
                    if ((byte >> (7 - z)) & 1) {
                        this->setPixel(x * 8 + z + anchorX, y + anchorY, mode);
                    }
                }
            }
        }

    }

    void OLEDDisplay::invertDisplay() {
        this->cmd(SSD1306_INVERTED_OFF | !this->inverted);
        inverted = !inverted;
    }

    int OLEDDisplay::cmd(unsigned char command) {
        // 0x00 is a byte indicating to ssd1306 that a command is being sent
        uint8_t data[2] = {0x00, command};
        //i2c_write_blocking(this->i2CInst, this->address, data, 2, false);
        I2CBUFF buf ={data,sizeof(data)};
        return Write(buf,2);
    }


    void OLEDDisplay::setContrast(unsigned char contrast) {
        this->cmd(SSD1306_CONTRAST);
        this->cmd(contrast);
    }

    void OLEDDisplay::setBuffer(unsigned char * buffer) {
        this->frameBuffer.setBuffer(buffer);
    }

    void OLEDDisplay::drawtext(int line, const char *buf ){
        drawText(this, font_8x8, buf, 0,line * 8);
    }
    void OLEDDisplay::drawtext(int line, uint32_t val){
        char buf[30];
        sprintf(buf,"%d",val);
        drawText(this, font_8x8, buf, 0, line * 8);
    }

    void OLEDDisplay::drawtext(int line, const std::string& s){
        drawText(this, font_8x8, s.c_str(), 0, line * 8);
    }

    void OLEDDisplay::drawRect ( uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, WriteMode mode ){
        drawrect(this, x_start, y_start, x_end, y_end,mode);
    }

    void OLEDDisplay::fillRect ( uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, WriteMode mode){
        fillrect(this, x_start, y_start, x_end, y_end,mode);
    }

    void OLEDDisplay::drawLine ( uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, WriteMode mode){
        drawline (this,  x0,  y0,  x1,  y1,  mode);
    }

    void OLEDDisplay::drawCircle(uint8_t xc, uint8_t yc, uint8_t radius, WriteMode mode){
        int x0 = xc - radius;
        int y0 = yc - radius;
        int x1 = xc + radius;
        int y1 = yc + radius;


        drawEllipse(x0,y0,x1,y1,mode);
    }

    void OLEDDisplay::fillCircle(uint8_t xc, uint8_t yc, uint8_t radius, WriteMode mode){
        int x0 = xc - radius;
        int y0 = yc - radius;
        int x1 = xc + radius;
        int y1 = yc + radius;

        fillEllipse(x0,y0,x1,y1,mode);
    }

    void OLEDDisplay::drawEllipse ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, WriteMode mode){
        int rx = abs(x1-x0)/2;
        int ry = abs(y1-y0)/2; 
        int xc = x0 + rx;
        int yc = y0 + ry;

        float dx, dy, d1, d2, x, y;
        x = 0;
        y = ry;
    
        // Initial decision parameter of region 1
        d1 = (ry * ry)
            - (rx * rx * ry)
            + (0.25 * rx * rx);
        dx = 2 * ry * ry * x;
        dy = 2 * rx * rx * y;
    
        // For region 1
        while (dx < dy) {
    
            // Print points based on 4-way symmetry
            // printf("(%f, %f)\n", x + xc, y + yc);
            // printf("(%f, %f)\n", -x + xc, y + yc);
            // printf("(%f, %f)\n", x + xc, -y + yc);
            // printf("(%f, %f)\n", -x + xc, -y + yc);
            setPixel(x + xc, y + yc,mode);
            setPixel(-x + xc, y + yc,mode);
            setPixel(x + xc, -y + yc,mode);
            setPixel(-x + xc, -y + yc,mode);
    
            // Checking and updating value of
            // decision parameter based on algorithm
            if (d1 < 0) {
                x++;
                dx = dx + (2 * ry * ry);
                d1 = d1 + dx + (ry * ry);
            }
            else {
                x++;
                y--;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d1 = d1 + dx - dy + (ry * ry);
            }
        }
    
        // Decision parameter of region 2
        d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
            + ((rx * rx) * ((y - 1) * (y - 1)))
            - (rx * rx * ry * ry);
    
        // Plotting points of region 2
        while (y >= 0) {
    
            // printing points based on 4-way symmetry
            // printf("(%f, %f)\n", x + xc, y + yc);
            // printf("(%f, %f)\n", -x + xc, y + yc);
            // printf("(%f, %f)\n", x + xc, -y + yc);
            // printf("(%f, %f)\n", -x + xc, -y + yc);
            setPixel(x + xc, y + yc,mode);
            setPixel(-x + xc, y + yc,mode);
            setPixel(x + xc, -y + yc,mode);
            setPixel(-x + xc, -y + yc,mode);
            // Checking and updating parameter
            // value based on algorithm
            if (d2 > 0) {
                y--;
                dy = dy - (2 * rx * rx);
                d2 = d2 + (rx * rx) - dy;
            }
            else {
                y--;
                x++;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d2 = d2 + dx - dy + (rx * rx);
            }
        }
    }
    void OLEDDisplay::fillEllipse ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, WriteMode mode){
        int rx = abs(x1-x0)/2;
        int ry = abs(y1-y0)/2; 
        int xc = x0 + rx;
        int yc = y0 + ry;

        float dx, dy, d1, d2, x, y;
        x = 0;
        y = ry;
    
        // Initial decision parameter of region 1
        d1 = (ry * ry)
            - (rx * rx * ry)
            + (0.25 * rx * rx);
        dx = 2 * ry * ry * x;
        dy = 2 * rx * rx * y;
    
        // For region 1
        while (dx < dy) {
    
            // Print points based on 4-way symmetry
            // printf("(%f, %f)\n", x + xc, y + yc);
            // printf("(%f, %f)\n", -x + xc, y + yc);
            // printf("(%f, %f)\n", x + xc, -y + yc);
            // printf("(%f, %f)\n", -x + xc, -y + yc);
            setPixel(x + xc, y + yc,mode);
            drawLine(xc, y + yc, x + xc, y + yc);

            setPixel(-x + xc, y + yc,mode);
            drawLine(xc, y + yc, -x + xc, y + yc);
            
            setPixel(x + xc, -y + yc,mode);
            drawLine(xc, -y + yc, x + xc, -y + yc);
            
            setPixel(-x + xc, -y + yc,mode);
            drawLine(xc, -y + yc, -x + xc, -y + yc);
    
            // Checking and updating value of
            // decision parameter based on algorithm
            if (d1 < 0) {
                x++;
                dx = dx + (2 * ry * ry);
                d1 = d1 + dx + (ry * ry);
            }
            else {
                x++;
                y--;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d1 = d1 + dx - dy + (ry * ry);
            }
        }
    
        // Decision parameter of region 2
        d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
            + ((rx * rx) * ((y - 1) * (y - 1)))
            - (rx * rx * ry * ry);
    
        // Plotting points of region 2
        while (y >= 0) {
    
            // printing points based on 4-way symmetry
            // printf("(%f, %f)\n", x + xc, y + yc);
            // printf("(%f, %f)\n", -x + xc, y + yc);
            // printf("(%f, %f)\n", x + xc, -y + yc);
            // printf("(%f, %f)\n", -x + xc, -y + yc);
            setPixel(x + xc, y + yc,mode);
            drawLine(xc, y + yc, x + xc, y + yc);

            setPixel(-x + xc, y + yc,mode);
            drawLine(xc, y + yc, -x + xc, y + yc);
            
            setPixel(x + xc, -y + yc,mode);
            drawLine(xc, -y + yc, x + xc, -y + yc);
            
            setPixel(-x + xc, -y + yc,mode);
            drawLine(xc, -y + yc, -x + xc, -y + yc);
            // Checking and updating parameter
            // value based on algorithm
            if (d2 > 0) {
                y--;
                dy = dy - (2 * rx * rx);
                d2 = d2 + (rx * rx) - dy;
            }
            else {
                y--;
                x++;
                dx = dx + (2 * ry * ry);
                dy = dy - (2 * rx * rx);
                d2 = d2 + dx - dy + (rx * rx);
            }
        }
    }
};