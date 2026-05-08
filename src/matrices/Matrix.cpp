//
// Created by xGrim on 2026-05-08.
//

#include "Matrix.h"

#include <stdexcept>

namespace rtc::matrices {

    Matrix::Matrix(std::initializer_list<std::initializer_list<float> > list) {
        rows = list.size();
        columns = list.begin()->size();

        data.reserve(rows * columns);

        for (const auto& row : list) {
            data.insert(data.end(), row.begin(), row.end());
        }
    }

    float &Matrix::operator[](const size_t r, const size_t c) {
        if (r >= rows || c >= columns) {
            throw std::out_of_range("invalid index");
        }

        return data[r * columns + c];
    }

    const float & Matrix::operator[](size_t r, size_t c) const {
        if (r >= rows || c >= columns) {
            throw std::out_of_range("invalid index");
        }

        return data[r * columns + c];
    }

    bool Matrix::operator==(const Matrix &m) const {
        if (rows != m.rows || columns != m.columns) {
            return false;
        }
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                if (data[r * columns + c] != m.data[r * columns + c]) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix Matrix::operator*(const Matrix &m) const {
        if (columns != m.rows) {
            throw std::invalid_argument("left matrix columns must be equal to right matrix rows");
        }
        Matrix result(rows, columns);
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < m.columns; c++) {
                float sum = 0.0f;
                for (size_t k = 0; k < columns; k++) {
                    sum += (*this)[r, k] * m[k, c];
                }
                result[r, c] = sum;
            }
        }
        return result;
    }

    Tuple Matrix::operator*(const Tuple &t) const {
        if (columns != 4) {
            throw std::invalid_argument("left matrix columns must be equal to right tuple length");
        }
        Tuple result;
        for (size_t r = 0; r < rows; ++r) {
            float sum = 0.0f;
            for (size_t c = 0; c < columns; ++c) {
                sum += (*this)[r, c] * t[c];
            }
            result[r] = sum;
        }
        return result;
    }

    Matrix Matrix::identity(const size_t n) {
        Matrix result(n, n);
        for (size_t i = 0; i < n; ++i) {
            result[i, i] = 1.0f;
        }
        return result;
    }

    Matrix Matrix::transpose() const {
        Matrix result(rows, columns);
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                result[c, r] = (*this)[r, c];
            }
        }
        return result;
    }
}
