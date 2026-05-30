//
// Created by xGrim on 2026-05-29.
//

#include "SmoothTriangle.h"

Vector triangles::SmoothTriangle::local_normal_at(const Point &p, const intersections::Intersection &i) const {
    return n2 * i.u + n3 * i.v + n1 * (1 - i.u - i.v);
}

bool triangles::SmoothTriangle::includes(const Shape &other) const {
    return this == &other;
}

bool triangles::SmoothTriangle::operator==(const Shape &other) const {
    if (!Shape::operator==(other)) return false;
    if (const auto o = dynamic_cast<const SmoothTriangle*>(&other); !o || p1 != o->p1 || p2 != o->p2 || p3 != o->p3 || n1 != o->n1 || n2 != o->n2 || n3 != o->n3) return false;
    return true;
}
