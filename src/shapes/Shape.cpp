//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Shape.h"

namespace rtc::shapes {
    Point Shape::world_to_obj(Point p) const {
        if (parent != nullptr) p = parent->world_to_obj(p);
        return transform.inverse() * p;
    }

    Vector Shape::normal_to_world(Vector normal) const {
        normal = transform.inverse().transpose() * normal;
        normal.w = 0;
        normal = normalize(normal);
        if (parent != nullptr) return parent->normal_to_world(normal);
        return normal;
    }

    bool Shape::operator==(const Shape& other) const {
        return (typeid(*this) == typeid(other) && transform == other.transform && material == other.material);
    }

    Vector Shape::normal_at(const Point &p, const intersections::Intersection& i) const {
        const Point local_point = world_to_obj(p);
        const Vector local_normal = local_normal_at(local_point, i);
        return normal_to_world(local_normal);
    }

}
