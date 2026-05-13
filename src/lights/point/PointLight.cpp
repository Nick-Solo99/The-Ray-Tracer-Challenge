//
// Created by Nicholas Solomon on 2026-05-11.
//

#include "PointLight.h"
#include <typeinfo>

namespace rtc::lights::point {

    bool PointLight::operator==(const Light& other) const {
        if (typeid(*this) != typeid(other)) {
            return false;
        }
        if (position != other.position || intensity != other.intensity) {
            return false;
        }
        return true;
    }

}
