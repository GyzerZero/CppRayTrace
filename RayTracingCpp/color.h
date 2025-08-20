#pragma once

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <cstdint>
#include <vector>

inline void write_color(vec3 color, std::vector<uint8_t> &pixelBuffer, int index)
{
    double r = color.x;
    double g = color.y;
    double b = color.z;

    pixelBuffer[index + 0] = uint8_t(r * 255.999);
    pixelBuffer[index + 1] = uint8_t(g * 255.999);
    pixelBuffer[index + 2] = uint8_t(b * 255.999);
}

#endif
