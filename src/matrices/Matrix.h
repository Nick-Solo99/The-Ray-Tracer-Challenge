//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_MATRIX_H
#define RTC_MATRIX_H

#include <iostream>
#include <vector>
#include "tuples/Tuple.h"


namespace rtc::matrices {
    using Tuple = tuples::Tuple;

    class Matrix {
    private:
        std::vector<float> data;
        size_t rows;
        size_t columns;

    public:
        Matrix(const size_t r, const size_t c) : data(r * c), rows(r), columns(c) {}
        Matrix(std::initializer_list<std::initializer_list<float>> list);

        float &operator[](size_t r, size_t c);
        const float &operator[](size_t r, size_t c) const;
        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const { return !(*this == m); }
        Matrix operator*(const Matrix& m) const;
        Tuple operator*(const Tuple& t) const;

        static Matrix identity(size_t n = 4);
        [[nodiscard]] Matrix transpose() const;
        [[nodiscard]] float determinant() const;
        [[nodiscard]] Matrix submatrix(size_t removeRow, size_t removeCol) const;
        [[nodiscard]] float minor(size_t removeRow, size_t removeCol) const;
        [[nodiscard]] float cofactor(size_t removeRow, size_t removeCol) const;
        [[nodiscard]] bool invertible() const;
        [[nodiscard]] Matrix inverse() const;
        [[nodiscard]] size_t getRows() const { return rows; }
        [[nodiscard]] size_t getColumns() const { return columns; }
    };

    std::ostream& operator<<(std::ostream& s, const Matrix& m);
}

#endif //RTC_MATRIX_H
