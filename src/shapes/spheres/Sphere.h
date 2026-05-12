//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H
#include <shapes/Shape.h>
#include <matrices/Matrix.h>

namespace rtc::shapes::spheres {
    class Sphere final : public Shape {
        public:
        matrices::Matrix transform = matrices::Matrix::identity();
        [[nodiscard]] std::vector<Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] tuples::Vector normal_at(const tuples::Point& p) const override;
        void set_transform(const matrices::Matrix& t) { transform = t; }
    };


}

#endif //RTC_SPHERE_H
