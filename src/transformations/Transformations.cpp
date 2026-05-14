//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Transformations.h"
#include "matrices/Matrix.h"
#include <cmath>
#include <numbers>

constexpr float PI = std::numbers::pi_v<float>;

namespace rtc::transformations {
    using Matrix = matrices::Matrix;

    Matrix translation(const float x, const float y, const float z) {
        Matrix result = Matrix::identity();
        result[0, 3] = x;
        result[1, 3] = y;
        result[2, 3] = z;
        return result;
    }

    Matrix scaling(const float x, const float y, const float z) {
        Matrix result = Matrix::identity();
        result[0, 0] = x;
        result[1, 1] = y;
        result[2, 2] = z;
        return result;
    }

    Matrix rotation_x(const float radians) {
        Matrix result = Matrix::identity();
        result[1, 1] = cosf(radians);
        result[1, 2] = -sinf(radians);
        result[2, 1] = sinf(radians);
        result[2, 2] = cosf(radians);
        return result;
    }

    Matrix rotation_y(const float radians) {
        Matrix result = Matrix::identity();
        result[0, 0] = cosf(radians);
        result[0, 2] = sinf(radians);
        result[2, 0] = -sinf(radians);
        result[2, 2] = cosf(radians);
        return result;
    }

    Matrix rotation_z(const float radians) {
        Matrix result = Matrix::identity();
        result[0, 0] = cosf(radians);
        result[0, 1] = -sinf(radians);
        result[1, 0] = sinf(radians);
        result[1, 1] = cosf(radians);
        return result;
    }

    Matrix shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy) {
        Matrix result = Matrix::identity();
        result[0, 1] = xy;
        result[0, 2] = xz;
        result[1, 0] = yx;
        result[1, 2] = yz;
        result[2, 0] = zx;
        result[2, 1] = zy;
        return result;
    }

    Transform& Transform::translate(const float x, const float y, const float z) {
        m = translation(x, y, z) * m;
        return *this;
    }

    Transform& Transform::scale(const float x, const float y, const float z) {
        m = scaling(x, y, z) * m;
        return *this;
    }

    Transform& Transform::rotate_x(const float radians) {
        m = rotation_x(radians) * m;
        return *this;
    }

    Transform& Transform::rotate_y(const float radians) {
        m = rotation_y(radians) * m;
        return *this;
    }

    Transform& Transform::rotate_z(const float radians) {
        m = rotation_z(radians) * m;
        return *this;
    }

    Transform& Transform::shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy) {
        m = transformations::shearing(xy, xz, yx, yz, zx, zy) * m;
        return *this;
    }

    Matrix view_transform(const Point from, const Point to, const Vector up) {
        const Vector forward = normalize(to - from);
        const Vector left = cross(forward, normalize(up));
        const Vector true_up = cross(left, forward);
        const Matrix orientation{
            {left.x, left.y, left.z, 0},
            {true_up.x, true_up.y, true_up.z, 0},
            {-forward.x, -forward.y, -forward.z, 0},
            {0, 0, 0, 1}
        };
        return orientation * translation(-from.x, -from.y, -from.z);
    }
}
