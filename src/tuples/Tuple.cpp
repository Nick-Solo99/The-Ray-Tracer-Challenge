//
// Created by Nicholas Solomon on 2026-05-07.
//

#include "Tuple.h"
#include <cmath>
#include <stdexcept>
#include <string>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::tuples {

    bool Tuple::isPoint() const{
        return std::fabs(w - 1.0f) < EPSILON;
    }

    bool Tuple::isVector() const{
        return std::fabs(w) < EPSILON;
    }

    bool Tuple::operator==(const Tuple& t) const {
        return std::fabs(x - t.x) < EPSILON &&
               std::fabs(y - t.y) < EPSILON &&
               std::fabs(z - t.z) < EPSILON &&
               std::fabs(w - t.w) < EPSILON;
    }

    bool Tuple::operator!=(const Tuple& t) const {
        return !(*this == t);
    }

    Tuple Tuple::operator+(const Tuple &t) const {
        return {x + t.x, y + t.y, z + t.z, w + t.w};
    }

    Tuple Tuple::operator-(const Tuple &t) const {
        return {x - t.x, y - t.y, z - t.z, w - t.w};
    }

    Tuple Tuple::operator-() const {
        return {-x, -y, -z, -w};
    }

    Tuple Tuple::operator*(const float s) const {
        return {x * s, y * s, z * s, w * s};
    }

    Tuple Tuple::operator*(const Tuple& t) const {
        return {x * t.x, y * t.y, z * t.z, w * t.w};
    }

    Tuple Tuple::operator/(const float s) const {
        return {x / s, y / s, z / s, w / s};
    }

    Tuple& Tuple::operator+=(const Tuple& t) {
        x += t.x;
        y += t.y;
        z += t.z;
        w += t.w;
        return *this;
    }

    Tuple& Tuple::operator-=(const Tuple& t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        w -= t.w;
        return *this;
    }

    float & Tuple::operator[](size_t i) {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("invalid index");
        }
    }

    const float & Tuple::operator[](size_t i) const {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("invalid index");
        }
    }

    Tuple Tuple::reflect(const Tuple &n) const {
        return *this - n * 2 * dot(*this, n);
    }


    std::ostream & operator<<(std::ostream &os, const Tuple &t) {
        return os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    }

    Tuple tuple(const float x, const float y, const float z, const float w) {
        return {x, y, z, w};
    }
    Tuple point(const float x, const float y, const float z) {
        return {x, y, z, 1.0};
    }
    Tuple vector(const float x, const float y, const float z) {
        return {x, y, z, 0.0};
    }

    Tuple color (const float r, const float g, const float b) {
        return {r, g, b, 0.0};
    }

    float magnitude(const Tuple& t) {
        return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
    }

    Tuple normalize(const Tuple& t) {
        const float mag = magnitude(t);
        return {t.x / mag, t.y / mag, t.z / mag, t.w / mag};
    }

    float dot(const Tuple& a, const Tuple& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    Tuple cross(const Tuple& a, const Tuple& b) {
        if (a.w != 0.0f || b.w != 0.0f) {
            throw std::invalid_argument("cross() requires vectors (w = 0), got w = " + std::to_string(a.w) + " and w = " + std::to_string(b.w));
        }
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
            0.0f};
    }

}
