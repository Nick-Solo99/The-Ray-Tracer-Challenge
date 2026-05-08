//
// Created by xGrim on 2026-05-07.
//

#include "Canvas.h"
#include <algorithm>
#include <cmath>
#include <sstream>


using namespace std;



namespace rtc::canvas {

    std::string Canvas::canvas_to_ppm() const {
        stringstream ss;
        ss << "P3\n";
        ss << width << " " << height << "\n";
        ss << "255\n";
        auto scale_color = [](const float c) {
            return static_cast<int>(std::round(std::clamp(c, 0.0f, 1.0f) * 255.0f));
        };
        for (int y = 0; y < height; ++y) {
            size_t lineLength = 0;
            for (int x = 0; x < width; ++x) {
                const size_t index = y * width + x;
                const int values[3] = {
                    scale_color(pixels[index].r),
                    scale_color(pixels[index].g),
                    scale_color(pixels[index].b)
                };
                for (size_t i = 0; i < 3; ++i ) {
                    std::string token = std::to_string(values[i]);
                    if (lineLength > 0) {
                        token = " " + token;
                    }
                    if (constexpr size_t MAX_LINE_LENGTH = 70; lineLength + token.size() > MAX_LINE_LENGTH) {
                        ss << "\n";
                        lineLength = 0;

                        token = std::to_string(values[i]);
                    }
                    ss << token;
                    lineLength += token.size();
                }
            }
            ss << "\n";
        }
        return ss.str();
    }


}
