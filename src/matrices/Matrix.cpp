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
}
