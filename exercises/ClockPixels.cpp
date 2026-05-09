//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <algorithm>
#include <canvas/Canvas.h>
#include <matrices/Matrix.h>
#include <transformations/Transformations.h>
#include <numbers>
#include <vector>
#include <iostream>
#include <fstream>

using Matrix = rtc::matrices::Matrix;
using Canvas = rtc::canvas::Canvas;
using Transform = rtc::transformations::Transform;

int main() {
    constexpr int CANVAS_WIDTH = 256;
    constexpr int CANVAS_HEIGHT = 256;
    constexpr float RADIUS = 256.0f * (3.0f/8.0f);
    Canvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    std::vector<Point> points(12);
    const Point noon = point(0, 0 ,1);
    points[0] = noon;
    for (size_t i = 0; i < points.size(); ++i) {
        const Matrix T = Transform().rotate_y(i * std::numbers::pi_v<float> / 6.0f).scale(RADIUS, RADIUS, RADIUS);
        points[i] = T * noon;
    }
    for (const auto& p : points) {

        const int values[2] = {
            std::clamp(static_cast<int>(std::round(CANVAS_WIDTH / 2 + p.x)), 0, CANVAS_WIDTH - 1),
            std::clamp(static_cast<int>(std::round(CANVAS_HEIGHT / 2 + p.z)), 0, CANVAS_HEIGHT - 1)
        };

        canvas.write_pixel(values[0], values[1], color(0.5f, 0.0f, 0.5f));
    }

    std::ofstream file("../output/clock.ppm");
    file << canvas.canvas_to_ppm();

    return 0;
}