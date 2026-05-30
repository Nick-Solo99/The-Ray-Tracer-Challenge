//
// Created by Nicholas Solomon on 2026-05-22.
//

#include "Group.h"
#include <intersections/Intersection.h>
#include <array>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::shapes::groups {
    std::array<float, 2> Group::check_axis(const float &origin, const float &direction, const float& min, const float& max) {
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

    bool Group::intersects_bounds(const Ray &r, const Bounds &b) {
        const auto& [min, max] = b;
        const auto [xtmin, xtmax] = check_axis(r.origin.x, r.direction.x, min.x, max.x);
        const auto [ytmin, ytmax] = check_axis(r.origin.y, r.direction.y, min.y, max.y);
        float tmin = std::max({xtmin, ytmin});
        float tmax = std::min({xtmax, ytmax});
        if (tmin > tmax) return false;
        const auto [ztmin, ztmax] = check_axis(r.origin.z, r.direction.z, min.z, max.z);
        tmin = std::max({tmin, ztmin});
        tmax = std::min({tmax, ztmax});
        return tmin <= tmax;
    }

    std::vector<intersections::Intersection> Group::intersect(const Ray &ray) const {
        const Ray ray2 = ray.transform(transform.inverse());

        if (!intersects_bounds(ray2, bounds())) return {};

        std::vector<intersections::Intersection> xs;
        for (int i{}; i < shapes.size(); ++i) {
            if (!intersects_bounds(ray2, child_bounds[i])) continue;
            const auto shape_xs = shapes[i]->intersect(ray2);
            xs.insert(xs.end(), shape_xs.begin(), shape_xs.end());
        }
        if (!xs.empty()) std::sort(xs.begin(), xs.end());
        return xs;
    }

    Vector Group::local_normal_at(const Point &p, const intersections::Intersection& i) const {
        return vector(0, 1, 0);
    }

    const Bounds& Group::bounds() const {
        if (cached_bounds) {
            return *cached_bounds;
        }
        cache_bounds();
        return *cached_bounds;
    }

    bool Group::includes(const Shape &other) const {
        for (const auto& shape : shapes) {
            if (shape->includes(other)) return true;
        }
        return false;
    }

    void Group::add_child(std::unique_ptr<Shape> shape) {
        shape->parent = this;
        shapes.push_back(std::move(shape));
    }

    void Group::cache_bounds() const {
        child_bounds.clear();
        child_bounds.reserve(shapes.size());

        Point group_min = point(INFINITY, INFINITY, INFINITY);
        Point group_max = point(-INFINITY, -INFINITY, -INFINITY);

        for (const auto& shape : shapes) {
            const auto& [min, max] = shape->bounds();

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

            Point new_min = point(INFINITY, INFINITY, INFINITY);
            Point new_max = point(-INFINITY, -INFINITY, -INFINITY);

            for (auto& c : corners) {
                c = shape->transform * c;

                new_min.x = std::min(new_min.x, c.x);
                new_min.y = std::min(new_min.y, c.y);
                new_min.z = std::min(new_min.z, c.z);

                new_max.x = std::max(new_max.x, c.x);
                new_max.y = std::max(new_max.y, c.y);
                new_max.z = std::max(new_max.z, c.z);
            }
            child_bounds.emplace_back(new_min, new_max);
            group_min.x = std::min(group_min.x, new_min.x);
            group_min.y = std::min(group_min.y, new_min.y);
            group_min.z = std::min(group_min.z, new_min.z);

            group_max.x = std::max(group_max.x, new_max.x);
            group_max.y = std::max(group_max.y, new_max.y);
            group_max.z = std::max(group_max.z, new_max.z);
        }
        cached_bounds = Bounds(group_min, group_max);
    }

    bool Group::contains(const Shape *shape) const {
        return std::ranges::any_of(shapes, [shape](const auto& ptr) {return ptr.get() == shape;});
    }

    void Group::set_material(const Material &material) const {
        for (const auto& shape : shapes) {
            if (const auto s = dynamic_cast<Group*>(shape.get())) {
                s->set_material(material);
            } else {
                shape->material = material;
            }
        }
    }

    bool Group::operator==(const Shape &shape) const {
        if (!Shape::operator==(shape)) return false;
        const auto* g = dynamic_cast<const Group*>(&shape);
        if (!g || g->size() != size()) return false;
        for (size_t i{}; i < size(); i++) {
            if ((*this)[i] != (*g)[i]) return false;
        }
        return true;
    }
}
