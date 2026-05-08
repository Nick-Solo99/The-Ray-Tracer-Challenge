//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "matrices/Matrix.h"
#include <iostream>

using namespace rtc::matrices;

int main() {

    std::cout << "Inverse of identity matrix:\n" << Matrix::identity().inverse() << std::endl;

    const Matrix A({{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}});

    std::cout << "Multiply matrix by its inverse:\n" << A * A.inverse() << std::endl;

    std::cout << "inverse transpose == transpose inverse: " << std::boolalpha << (A.transpose().inverse() == A.inverse().transpose()) << std::endl;

    return 0;
}