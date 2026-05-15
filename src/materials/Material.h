//
// Created by Nicholas Solomon on 2026-05-11.
//

#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include <tuples/Tuple.h>
#include <patterns/Pattern.h>
#include <memory>

namespace rtc::lights {
    struct Light;
}

using namespace rtc::tuples;
using namespace rtc::patterns;

namespace rtc::materials {
    using Light = lights::Light;

    struct Material {
        Color color = tuples::color(1, 1, 1);
        float ambient = 0.1f;
        float diffuse = 0.9f;
        float specular = 0.9f;
        float shininess = 200.0f;
        std::unique_ptr<Pattern> pattern = nullptr;

        Material() = default;
        Material(const Color& color, const float ambient, const float diffuse, const float specular, const float shininess, std::unique_ptr<Pattern> pattern = nullptr)
        : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), pattern(std::move(pattern)) {}
        Material(const Material& other) : color(other.color), ambient(other.ambient), diffuse(other.diffuse), specular(other.specular), shininess(other.shininess),pattern(other.pattern ? other.pattern->clone() : nullptr){}
        Material& operator=(const Material& other) {
            if (this != &other) {
                color = other.color;
                ambient = other.ambient;
                diffuse = other.diffuse;
                specular = other.specular;
                shininess = other.shininess;
                pattern = other.pattern ? other.pattern->clone() : nullptr;
            }
            return *this;
        }
        Material(Material&&) = default;
        Material& operator=(Material&&) = default;



        bool operator==(const Material& other) const { return color == other.color && ambient == other.ambient && diffuse == other.diffuse && specular == other.specular && shininess == other.shininess; }

        [[nodiscard]] Color lighting(const Light& light, const Point& pos, const Vector& eye_v, const Vector& normal_v, const bool& in_shadow = false) const;
    };
}

#endif //RTC_MATERIAL_H
