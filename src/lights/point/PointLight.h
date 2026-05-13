//
// Created by Nicholas Solomon on 2026-05-11.
//

#ifndef RTC_POINTLIGHT_H
#define RTC_POINTLIGHT_H

#include <lights/Light.h>

namespace rtc::lights::point {
    struct PointLight final : Light {

        bool operator==(const Light& other) const override;

        PointLight() = default;

        PointLight(const Tuple pos, const Tuple inten) { position = pos; intensity = inten; }
    };
}

#endif //RTC_POINTLIGHT_H
