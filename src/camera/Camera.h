//
// Created by Nicholas Solomon on 2026-05-13.
//

#ifndef RTC_CAMERA_H
#define RTC_CAMERA_H
#include <matrices/Matrix.h>
#include <rays/Ray.h>
#include <canvas/Canvas.h>
#include <world/World.h>

namespace rtc::camera {
    struct Camera {
        int hsize{};
        int vsize{};
        float fov{};
        matrices::Matrix transform = matrices::Matrix::identity();

        [[nodiscard]] float half_width() const;
        [[nodiscard]] float half_height() const;
        [[nodiscard]] float pixel_size() const;
        [[nodiscard]] rays::Ray ray_for_pixel(float x, float y) const;
        [[nodiscard]] canvas::Canvas render(const world::World& w) const;
    };
} // camera
// rtc

#endif //RTC_CAMERA_H