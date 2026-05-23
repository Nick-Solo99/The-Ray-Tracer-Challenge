//
// Created by Nicholas Solomon on 2026-05-21.
//

#ifndef RTC_CUBE_H
#define RTC_CUBE_H

#include <shapes/Shape.h>
#include <array>

namespace rtc::shapes::cubes {
    class Cube final : public Shape{
        [[nodiscard]] std::array<float, 2> check_axis(const float& origin, const float& direction) const;
    public:
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const rays::Ray& ray) const override;
        [[nodiscard]] Vector normal_at(const Point &p) const override;
    };
}


#endif //RTC_CUBE_H