#pragma once

#ifndef SSD1306_SHAPERENDERER_H
#define SSD1306_SHAPERENDERER_H

#include <math.h>
#include "OLEDDisplay.hpp"

namespace srbots {

    /// \brief Draws a line from x0, y0 to x1, y1.
    /// It supports all drawing angles
    /// \param ssd1306 - is the pointer to a SSD1306 object aka an initialised display
    /// \param x0, y0, x1, y1 are the start and end coordinates between which the line will be drawn
    /// \param mode - mode describes setting behavior. See WriteMode doc for more information
    void drawline (srbots::OLEDDisplay *ssd1306, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, srbots::WriteMode mode = srbots::WriteMode::ADD);

    /// \brief Draws a 1px wide rectangle between x0, y0 and x1, y1
    /// \param x_start, x_end, y_start, y_end - corner points for the rectangle
    /// \param mode - mode describes setting behavior. See WriteMode doc for more information
    void drawrect (srbots::OLEDDisplay *ssd1306, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, srbots::WriteMode mode = srbots::WriteMode::ADD);

    /// \brief Fills a rectangle from x0, y0 to x1, y1
    /// \param x_start, x_end, y_start, y_end - corner points for the rectangle
    /// \param mode - mode describes setting behavior. See WriteMode doc for more information
    void fillrect (srbots::OLEDDisplay *ssd1306 , uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, srbots::WriteMode mode = srbots::WriteMode::ADD);

};
#endif //SSD1306_SHAPERENDERER_H
