//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H
#include <shapes/Shape.h>
#include <matrices/Matrix.h>

namespace rtc::shapes::spheres {
    class Sphere final : public Shape {
        public:
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] tuples::Vector local_normal_at(const tuples::Point& p) const override;
        [[nodiscard]] Bounds bounds() const override;

        //return a glass sphere
        static Sphere glass();
    };


}

#endif //RTC_SPHERE_H
