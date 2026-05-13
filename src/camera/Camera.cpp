//
// Created by Nicholas Solomon on 2026-05-13.
//

#include "Camera.h"

namespace rtc::camera {
    float Camera::half_width() const {
        const float half_view = std::tanf(fov/2.f);
        const float aspect = static_cast<float>(hsize) / static_cast<float>(vsize);
        if (aspect >= 1) {
            return half_view;
        }
        return half_view * aspect;
    }

    float Camera::half_height() const {
        const float half_view = std::tanf(fov/2.f);
        const float aspect = static_cast<float>(hsize) / static_cast<float>(vsize);
        if (aspect >= 1) {
            return half_view / aspect;
        }
        return half_view;
    }

    float Camera::pixel_size() const {
        return (half_width() * 2.f) / hsize;
    }

    rays::Ray Camera::ray_for_pixel(float x, float y) const {
        const float offset_x = (x + 0.5) * pixel_size();
        const float offset_y = (y + 0.5) * pixel_size();

        const float world_x = half_width() - offset_x;
        const float world_y = half_height() - offset_y;

        const Point pixel = transform.inverse() * point(world_x, world_y, -1);
        const Point origin = transform.inverse() * point(0, 0, 0);
        const Vector direction = normalize(pixel - origin);

        return rays::Ray(origin, direction);
    }

    canvas::Canvas Camera::render(const world::World &w) const {
        canvas::Canvas image{hsize, vsize};
        for (int y = 0; y < vsize; y++) {
            for (int x = 0; x < hsize; x++) {
                const rays::Ray r = ray_for_pixel(x, y);
                const Color color = w.color_at(r);
                image.write_pixel(x, y, color);
            }
        }
        return image;
    }
} // camera
// rtc