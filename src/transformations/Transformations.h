//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_TRANSFORMATIONS_H
#define RTC_TRANSFORMATIONS_H

namespace rtc::matrices {
    class Matrix;
}

namespace rtc::transformations {
    using Matrix = matrices::Matrix;
    Matrix translation(const float x, const float y, const float z);
    Matrix scaling(const float x, const float y, const float z);
    Matrix rotation_x(const float radians);
}

#endif //RTC_TRANSFORMATIONS_H
