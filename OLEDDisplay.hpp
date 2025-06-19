#pragma once

#ifndef SSD1306_SSD1306_H
#define SSD1306_SSD1306_H
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "hardware/i2c.h"
#include "MyI2CInitStuff.hpp"
#include "FrameBuffer.h"

namespace srbots {

    /// Register addresses from datasheet
    enum REG_ADDRESSES : unsigned char{
        SSD1306_CONTRAST = 0x81,
        SSD1306_DISPLAYALL_ON_RESUME = 0xA4,
        SSD1306_DISPLAYALL_ON = 0xA5,
        SSD1306_INVERTED_OFF = 0xA6,
        SSD1306_INVERTED_ON = 0xA7,
        SSD1306_DISPLAY_OFF = 0xAE,
        SSD1306_DISPLAY_ON = 0xAF,
        SSD1306_DISPLAYOFFSET = 0xD3,
        SSD1306_COMPINS = 0xDA,
        SSD1306_VCOMDETECT = 0xDB,
        SSD1306_DISPLAYCLOCKDIV = 0xD5,
        SSD1306_PRECHARGE = 0xD9,
        SSD1306_MULTIPLEX = 0xA8,
        SSD1306_LOWCOLUMN = 0x00,
        SSD1306_HIGHCOLUMN = 0x10,
        SSD1306_STARTLINE = 0x40,
        SSD1306_MEMORYMODE = 0x20,
        SSD1306_MEMORYMODE_HORZONTAL = 0x00,
        SSD1306_MEMORYMODE_VERTICAL = 0x01,
        SSD1306_MEMORYMODE_PAGE = 0x10,
        SSD1306_COLUMNADDR = 0x21,
        SSD1306_PAGEADDR = 0x22,
        SSD1306_COM_REMAP_OFF = 0xC0,
        SSD1306_COM_REMAP_ON = 0xC8,
        SSD1306_CLUMN_REMAP_OFF = 0xA0,
        SSD1306_CLUMN_REMAP_ON = 0xA1,
        SSD1306_CHARGEPUMP = 0x8D,
        SSD1306_EXTERNALVCC = 0x1,
        SSD1306_SWITCHCAPVCC = 0x2,
    };

    /// \enum Size
    enum class Size {
        /// Display size W128xH64
        W128xH64,
        /// Display size W128xH32
        W128xH32
    };

    /// \enum WriteMode
    enum class WriteMode : const unsigned char{
        /// sets pixel on regardless of its state
        ADD = 0,
        /// sets pixel off regardless of its state
        SUBTRACT = 1,
        /// inverts pixel, so 1->0 or 0->1
        INVERT = 2,
    };

    enum OLED_ORIENTATION {NORMAL=0, UPSIDEDOWN=1};


    /// \brief OLEDDisplay represents an OLED display
    class OLEDDisplay : public I2CSensor{
    private:
        i2c_inst *i2CInst;
        uint16_t address;
        Size size;

        FrameBuffer frameBuffer;

        uint8_t width, height;

        bool inverted;

        /// \brief Sends single 8bit command to ssd1306 controller
        /// \param command - byte to be sent to controller
        int  cmd(unsigned char command);
        OLED_ORIENTATION _orientation;
    public:
        /// \brief  constructor initialized display and sets all required registers for operation
        /// \param i2CInst - i2c instance. Either i2c0 or i2c1
        /// \param Address - display i2c address. usually for 128x32 0x3C and for 128x64 0x3D
        /// \param size - display size. Acceptable values W128xH32 or W128xH64
        //SSD1306(i2c_inst *i2CInst, uint16_t Address, Size size);

        OLEDDisplay(i2cbus* i2cport, OLED_ORIENTATION orientation=NORMAL, uint16_t Address=0x3D, Size size=Size::W128xH64);

	
        /// \brief Set pixel operates frame buffer...
        /// x is the x position of pixel you want to change. values 0 - 127
        /// y is the y position of pixel you want to change. values 0 - 31 or 0 - 63
        /// \param x - position of pixel you want to change. values 0 - 127
        /// \param y - position of pixel you want to change. values 0 - 31 or 0 - 63
        /// \param mode - mode describes setting behavior. See WriteMode doc for more information
        void setPixel(int16_t x, int16_t y, WriteMode mode = WriteMode::ADD);

        /// \brief Sends frame buffer to display so that it updated
        void sendBuffer();

        /// \brief Sends frame buffer to display so that it updated - must ALWAYS call this to update the display
        void updateDisplay(){sendBuffer();}
		
		/// \brief returns the width of the screen (almost always 128)
        int screenwidth(){return this->width;}
		/// \brief returns the height of the screen (either 32 or 64)
        int screenheight(){return this->height;}

        /// \brief Adds bitmap image to frame buffer
        /// \param anchorX - sets start point of where to put the image on the screen
        /// \param anchorY - sets start point of where to put the image on the screen
        /// \param image_width - width of the image in pixels
        /// \param image_height - height of the image in pixels
        /// \param image - pointer to uint8_t (unsigned char) array containing image data
        /// \param mode - mode describes setting behavior. See WriteMode doc for more information
        void addBitmapImage(int16_t anchorX, int16_t anchorY, uint8_t image_width, uint8_t image_height, uint8_t *image,
                            WriteMode mode = WriteMode::ADD);

        /// \brief Manually set frame buffer. make sure it's correct size of 1024 bytes
        /// \param buffer is an array of 1024 bytes
        void setBuffer(unsigned char *buffer);

        /// \brief Flips the display
        /// \param orientation - 0 for not flipped, 1 for flipped display
        int setOrientation(bool orientation);

        /// \brief Clears frame buffer aka set all bytes to 0
        void clear();

        /// \brief Inverts screen on hardware level. Way more efficient than setting buffer to all ones and then using WriteMode subtract.
        void invertDisplay();

        /// \brief Sets display contrast according to ssd1306 documentation
        /// \param contrast - accepted values of 0 to 255 to set the contrast
        void setContrast(unsigned char contrast);

        /// \brief Initializes OLED display
        bool init();

        /// \brief Writes text to OLED buffer - DOES NOT DISPLAY
        ///  Must call updateDisplay() to display changes
        /// \param line 0 or 1 for the line number
        /// \param buf a text string
        void drawtext(int line, const char *buf);
		void drawText(int line, const char *buf){drawtext( line, buf);}

        /// \brief Writes text to OLED buffer - DOES NOT DISPLAY
        ///  Must call updateDisplay() to display changes
        /// \param line  0 or 1 for the line number 
        /// \param val   a value
        void drawtext(int line, int val);
		void drawText(int line, int val){drawtext( line,  val);}
		
		/// \brief Writes text to OLED buffer - DOES NOT DISPLAY
        ///  Must call updateDisplay() to display changes
        /// \param line  0 or 1 for the line number 
        /// \param val   a value
        void drawtext(int line, double val);
		void drawText(int line, double val){drawtext( line,  val);}
    
        /// \brief Writes text to OLED buffer - DOES NOT DISPLAY
        ///  Must call updateDisplay() to display changes
        /// \param line  0 or 1 for the line number
        /// @param s the string to write out.
        void drawtext(int line, const std::string& s);
		void drawText(int line, const std::string& s){drawtext(line, s);}
    

        /// @brief draws a rectangle on the screen
        /// @param x_start x coord of top left of the rectangle
        /// @param y_start y coord of top left of the rectangle
        /// @param x_end   x coord of bottom right of the rectangle
        /// @param y_end   y coord of bottom right of the rectangle
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT
        void drawRect   ( uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, WriteMode mode = WriteMode::ADD);

        /// @brief draws a filled in rectangle 
        /// @param x_start x coord of top left of the rectangle
        /// @param y_start y coord of top left of the rectangle
        /// @param x_end   x coord of bottom right of the rectangle
        /// @param y_end   y coord of bottom right of the rectangle
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT
        void fillRect   ( uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, WriteMode mode = WriteMode::ADD);

        /// @brief draws a line
        /// @param x_start x coord of top left of the line
        /// @param y_start y coord of top left of the line
        /// @param x_end   x coord of bottom right of the line
        /// @param y_end   y coord of bottom right of the line
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT
        void drawLine   ( uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, WriteMode mode = WriteMode::ADD);

        /// @brief draws an ellipse inside of a given rectangle
        /// @param x_start x coord of top left of the rectangle
        /// @param y_start y coord of top left of the rectangle
        /// @param x_end   x coord of bottom right of the rectangle
        /// @param y_end   y coord of bottom right of the rectangle
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT
        void drawEllipse( int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end, WriteMode mode = WriteMode::ADD);

        /// @brief draws a filled ellipse inside of a given rectangle
        /// @param x_start x coord of top left of the rectangle
        /// @param y_start y coord of top left of the rectangle
        /// @param x_end   x coord of bottom right of the rectangle
        /// @param y_end   y coord of bottom right of the rectangle
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT       
        void fillEllipse( int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end, WriteMode mode = WriteMode::ADD);

        /// @brief draws a circle
        /// @param centerx center point for x
        /// @param centery center point for y
        /// @param radius  radius from center
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT 
        void drawCircle ( uint8_t centerx, uint8_t centery, uint8_t radius, WriteMode mode = WriteMode::ADD);

        /// @brief draws a filled in circle
        /// @param centerx center point for x
        /// @param centery center point for y
        /// @param radius  radius from center
        /// @param mode    WriteMode enum ADD, SUBTRACT, INVERT 
        void fillCircle ( uint8_t centerx, uint8_t centery, uint8_t radius, WriteMode mode = WriteMode::ADD);
    };
};
#endif //SSD1306_SSD1306_H