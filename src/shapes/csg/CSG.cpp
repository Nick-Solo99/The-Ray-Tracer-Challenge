//
// Created by Nicholas Solomon on 2026-05-30.
//

#include "CSG.h"
#include <intersections/Intersection.h>

namespace rtc::shapes::csg {
    std::vector<intersections::Intersection> CSG::intersect(const Ray &ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        const auto leftxs = left->intersect(ray2);
        const auto rightxs = right->intersect(ray2);
        std::vector<intersections::Intersection> xs;
        std::merge(leftxs.begin(), leftxs.end(), rightxs.begin(), rightxs.end(), std::back_inserter(xs));
        return filter_intersections(xs);
    }

    Vector CSG::local_normal_at(const Point &p, const intersections::Intersection &i) const {
        return vector(0, 1, 0);
    }

    const Bounds & CSG::bounds() const {
        if (cached_bounds) {
            return *cached_bounds;
        }
        cached_bounds = {point(0, 0, 0), point(1, 1, 1)};
        return *cached_bounds;
    }

    bool CSG::includes(const Shape &other) const {
        return left->includes(other) || right->includes(other);
    }

    std::vector<intersections::Intersection> CSG::filter_intersections(std::vector<intersections::Intersection> xs) const {
        bool inl = false;
        bool inr = false;
        std::vector<intersections::Intersection> result;
        for (const auto& i : xs) {
            const bool lhit = left->includes(*i.object);
            if (intersection_allowed(op, lhit, inl, inr)) {
                result.push_back(i);
            }
            if (lhit) {
                inl = !inl;
            } else {
                inr = !inr;
            }
        }
        return result;
    }

    bool intersection_allowed(const Operation &op, const bool lhit, const bool inl, const bool inr) {
        switch (op) {
            case Operation::UNION:
                return (lhit && !inr) || (!lhit && !inl);
            case Operation::INTERSECT:
                return (lhit && inr) || (!lhit && inl);
            case Operation::DIFFERENCE:
                return (lhit && !inr) || (!lhit && inl);
            default:
                return false;
        }
    }
}
