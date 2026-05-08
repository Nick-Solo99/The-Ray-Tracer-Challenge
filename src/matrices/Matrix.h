//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_MATRIX_H
#define RTC_MATRIX_H

#include <vector>

namespace rtc::matrices {
    class Matrix {
    private:
        std::vector<float> data;
        size_t rows;
        size_t columns;

    public:
        Matrix(const size_t r, const size_t c) : data(r * c), rows(r), columns(c) {}
        Matrix(std::initializer_list<std::initializer_list<float>> list);

        float &operator[](size_t r, size_t c);
        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const { return !(*this == m); }
    };
}

#endif //RTC_MATRIX_H
