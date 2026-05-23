//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Shape.h"

namespace rtc::shapes {
    bool Shape::operator==(const Shape& other) const {
        return (typeid(*this) == typeid(other) && transform == other.transform && material == other.material);
    }

}
