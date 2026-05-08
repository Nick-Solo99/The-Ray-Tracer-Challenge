//
// Created by xGrim on 2026-05-07.
//

#ifndef RTC_CANVAS_H
#define RTC_CANVAS_H

#include <vector>
#include <string>

#include "tuples/Tuple.h"

using namespace rtc::tuples;

namespace rtc::canvas {
    struct Canvas {
        int width, height;
        std::vector<Tuple> pixels;

        Canvas(const int width, const int height) :
        width(width), height(height), pixels(width * height, color(0.0f, 0.0f, 0.0f)) {}

        void write_pixel(const int x, const int y, const Color& c) { pixels[x + y * width] = c;}
        Color pixel_at(const int x, const int y) const { return pixels[x + y * width]; }

        std::string canvas_to_ppm() const;

    };
}

#endif //RTC_CANVAS_H
