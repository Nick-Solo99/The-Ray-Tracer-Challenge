//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_TRANSFORMATIONS_H
#define RTC_TRANSFORMATIONS_H
#include "matrices/Matrix.h"


namespace rtc::transformations {
    using Matrix = matrices::Matrix;
    Matrix translation(float x, float y, float z);
    Matrix scaling(float x, float y, float z);
    Matrix rotation_x(float radians);
    Matrix rotation_y(float radians);
    Matrix rotation_z(float radians);
    Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

    class Transform {
        public:
        Matrix m;

        Transform() : m(Matrix::identity()) {}

        Transform& translate(float x, float y, float z);
        Transform& scale(float x, float y, float z);
        Transform& rotate_x(float radians);
        Transform& rotate_y(float radians);
        Transform& rotate_z(float radians);
        Transform& shearing(float xy, float xz, float yx, float yz, float zx, float zy);

        operator Matrix() const { return m; };
    };
}

#endif //RTC_TRANSFORMATIONS_H
