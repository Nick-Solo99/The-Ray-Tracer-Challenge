//
// Created by xGrim on 2026-05-08.
//

#include "Matrix.h"

#include <stdexcept>

namespace rtc::matrices {

    constexpr float EPSILON = 0.00001f;

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
                if (std::fabs(data[r * columns + c] - m.data[r * columns + c]) > EPSILON) {
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
        Matrix result(rows, m.columns);
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
        Matrix result(columns, rows);
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                result[c, r] = (*this)[r, c];
            }
        }
        return result;
    }

    float Matrix::determinant() const {
        if (rows != columns) {
            throw std::invalid_argument("determinant requires a square matrix");
        }

        if (rows == 2) {
            return (*this)[0, 0] * (*this)[1, 1] - (*this)[0, 1] * (*this)[1, 0];
        }

        float det = 0.0f;
        for (size_t c = 0; c < columns; ++c) {
            det += (*this)[0, c] * cofactor(0, c);
        }
        return det;
    }

    Matrix Matrix::submatrix(const size_t removeRow,const size_t removeCol) const {

        if (removeRow >= rows || removeCol >= columns) {
            throw std::out_of_range("invalid index");
        }

        Matrix result(rows - 1, columns - 1);
        size_t r2 = 0;
        for (size_t r = 0; r < rows; r++) {
            if (r == removeRow) { continue; }
            size_t c2 = 0;
            for (size_t c = 0; c < columns; c++) {
                if (c == removeCol) { continue; }
                result[r2, c2] = (*this)[r, c];
                c2++;
            }
            r2++;
        }
        return result;
    }

    float Matrix::minor(const size_t removeRow, const size_t removeCol) const {
        return submatrix(removeRow, removeCol).determinant();
    }

    float Matrix::cofactor(const size_t removeRow, const size_t removeCol) const {
        return (removeRow + removeCol) % 2 != 0 ? -minor(removeRow, removeCol) : minor(removeRow, removeCol);
    }

    bool Matrix::invertible() const {
        return std::fabs(determinant()) > EPSILON;
    }

    Matrix Matrix::inverse() const {
        if (!invertible()) {
            throw std::invalid_argument("matrix is not invertible");
        }
        Matrix result(rows, columns);
        const float det = determinant();
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < columns; c++) {
                result[c, r] = cofactor(r, c) / det;
            }
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& s, const Matrix& m) {
        for (size_t r = 0; r < m.getRows(); ++r) {
            s << "[ ";
            for (size_t c = 0; c < m.getColumns(); ++c) {
                s << m[r, c];
                if (c + 1 < m.getColumns()) {
                    s << ", ";
                }
            }
            s << " ]";
            if (r + 1 < m.getRows()) {
                s << "\n";
            }
        }
        return s;
    }
}
