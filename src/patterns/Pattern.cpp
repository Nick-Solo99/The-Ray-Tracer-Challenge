//
// Created by Nicholas Solomon on 2026-05-14.
//

#include "Pattern.h"
#include <shapes/Shape.h>

using namespace rtc::shapes;

    namespace rtc::patterns {
        Color Pattern::color_at_obj(const Shape& obj, const Point& point) const {
            const Point obj_point = obj.transform.inverse() * point;
            const Point pattern_point = transform.inverse() * obj_point;
            return color_at(pattern_point);
        }
    } // patterns
// rtc