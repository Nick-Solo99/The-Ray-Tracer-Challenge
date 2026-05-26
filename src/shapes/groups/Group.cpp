//
// Created by Nicholas Solomon on 2026-05-22.
//

#include "Group.h"
#include <intersections/Intersection.h>
#include <array>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::shapes::groups {
    std::array<float, 2> Group::check_axis(const float &origin, const float &direction, const float& min, const float& max) const {
        const float tmin_numerator = (min - origin);
        const float tmax_numerator = (max - origin);
        float tmin, tmax;
        if (std::fabs(direction) >= EPSILON) {
            tmin = tmin_numerator / direction;
            tmax = tmax_numerator / direction;
        } else {
            tmin = tmin_numerator < 0 ? -INFINITY : INFINITY;
            tmax = tmax_numerator < 0 ? -INFINITY : INFINITY;
        }
        if (tmin > tmax) {
            std::swap(tmin, tmax);
        }
        return { tmin, tmax };
    }

    std::vector<intersections::Intersection> Group::intersect(const Ray &ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        const auto [min, max] = Group::bounds();
        const auto [xtmin, xtmax] = check_axis(ray2.origin.x, ray2.direction.x, min.x, max.x);
        const auto [ytmin, ytmax] = check_axis(ray2.origin.y, ray2.direction.y, min.y, max.y);
        float tmin = std::max({xtmin, ytmin});
        float tmax = std::min({xtmax, ytmax});

        if (tmin > tmax) return {};

        const auto [ztmin, ztmax] = check_axis(ray2.origin.z, ray2.direction.z, min.z, max.z);

        tmin = std::max({tmin, ztmin});
        tmax = std::min({tmax, ztmax});
        if (tmin > tmax) return {};

        std::vector<intersections::Intersection> xs;
        for (const auto& shape : shapes) {
            const auto shape_xs = shape->intersect(ray2);
            xs.insert(xs.end(), shape_xs.begin(), shape_xs.end());
        }
        if (!xs.empty()) std::sort(xs.begin(), xs.end());
        return xs;
    }

    Vector Group::local_normal_at(const Point &p) const {
        return vector(0, 1, 0);
    }

    Bounds Group::bounds() const {
        Point group_min = point(INFINITY, INFINITY, INFINITY);
        Point group_max = point(-INFINITY, -INFINITY, -INFINITY);

        for (const auto& shape : shapes) {
            auto[min, max] = shape->bounds();

            std::array corners = {
                point(min.x, min.y, min.z),
                point(max.x, min.y, min.z),
                point(max.x, max.y, min.z),
                point(min.x, max.y, min.z),
                point(min.x, min.y, max.z),
                point(max.x, min.y, max.z),
                point(min.x, max.y, max.z),
                point(max.x, max.y, max.z)
            };

            for (auto corner : corners) {
                corner = shape->transform * corner;

                group_min.x = std::min(group_min.x, corner.x);
                group_min.y = std::min(group_min.y, corner.y);
                group_min.z = std::min(group_min.z, corner.z);

                group_max.x = std::max(group_max.x, corner.x);
                group_max.y = std::max(group_max.y, corner.y);
                group_max.z = std::max(group_max.z, corner.z);
            }
        }
        return Bounds(group_min, group_max);
    }

    void Group::add_child(std::unique_ptr<Shape> shape) {
        shape->parent = this;
        shapes.push_back(std::move(shape));
    }

    bool Group::contains(const Shape *shape) const {
        return std::ranges::any_of(shapes, [shape](const auto& ptr) {return ptr.get() == shape;});
    }
}
