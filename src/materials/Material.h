//
// Created by Nicholas Solomon on 2026-05-11.
//

#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include <tuples/Tuple.h>

namespace rtc::lights {
    struct Light;
}

using namespace rtc::tuples;

namespace rtc::materials {
    using Light = lights::Light;

    struct Material {
        Color color = tuples::color(1, 1, 1);
        float ambient = 0.1f;
        float diffuse = 0.9f;
        float specular = 0.9f;
        float shininess = 200.0f;

        bool operator==(const Material& other) const { return color == other.color && ambient == other.ambient && diffuse == other.diffuse && specular == other.specular && shininess == other.shininess; }

        Color lighting(const Light& light, const Point& pos, const Vector& eye_v, const Vector& normal_v);
    };
}

#endif //RTC_MATERIAL_H
