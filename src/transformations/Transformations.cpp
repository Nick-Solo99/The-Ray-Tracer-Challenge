//
// Created by xGrim on 2026-05-08.
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

}
