//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_TRANSFORMATIONS_H
#define RTC_TRANSFORMATIONS_H
#include "matrices/Matrix.h"


namespace rtc::transformations {
    using Matrix = matrices::Matrix;
    Matrix translation(const float x, const float y, const float z);
    Matrix scaling(const float x, const float y, const float z);
    Matrix rotation_x(const float radians);
    Matrix rotation_y(const float radians);
    Matrix rotation_z(const float radians);
    Matrix shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy);

    class Transform {
        public:
        Matrix m;

        Transform() : m(Matrix::identity()) {}

        Transform& translate(const float x, const float y, const float z);
        Transform& scale(const float x, const float y, const float z);
        Transform& rotate_x(const float radians);
        Transform& rotate_y(const float radians);
        Transform& rotate_z(const float radians);
        Transform& shearing(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy);

        operator Matrix() const { return m; };
    };
}

#endif //RTC_TRANSFORMATIONS_H
