//
// Created by Nicholas Solomon on 2026-05-11.
//

#include "Material.h"

#include <cmath>
#include <lights/Light.h>

namespace rtc::materials {

    Color Material::lighting(const Shape& obj, const Light &light, const Point &pos, const Vector &eye_v, const Vector &normal_v, const bool& in_shadow) const {
        Color active_color = color;
        if (pattern != nullptr) {
            active_color = pattern->color_at_obj(obj, pos);
        }

        const Color effective_color = active_color * light.intensity;
        const Vector light_v = normalize(light.position - pos);
        const Color ambient_cont = effective_color * this->ambient ;
        const float light_dot_normal = dot(light_v, normal_v);

        Color diffuse_cont;
        Color specular_cont;

        if (light_dot_normal < 0) {
            diffuse_cont = tuples::color(0, 0, 0);
            specular_cont = tuples::color(0, 0, 0);
        } else {
            diffuse_cont = effective_color * this->diffuse * light_dot_normal;

            const Vector reflect_v = -light_v.reflect(normal_v);
            const float reflect_dot_eye = dot(reflect_v, eye_v);

            if (reflect_dot_eye <= 0) {
                specular_cont = tuples::color(0, 0, 0);
            } else {
                const float factor = pow(reflect_dot_eye, shininess);
                specular_cont = light.intensity * this->specular * factor;
            }
        }

        return in_shadow ? ambient_cont : diffuse_cont + specular_cont + ambient_cont ;
    }


}
