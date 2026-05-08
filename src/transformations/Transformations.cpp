//
// Created by xGrim on 2026-05-08.
//

#include "Transformations.h"
#include "matrices/Matrix.h"

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

}
