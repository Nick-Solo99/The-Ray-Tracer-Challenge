//
// Created by Nicholas Solomon on 2026-05-07.
//

#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H
#include <iostream>


namespace rtc::tuples {

    struct Tuple {
        union {
            struct {float x, y, z, w;};
            struct {float r, g, b, a;};
        };


        [[nodiscard]] bool isPoint() const;
        [[nodiscard]] bool isVector() const;

        bool operator==(const Tuple& t) const;
        bool operator!=(const Tuple& t) const;
        bool operator<(const Tuple& t) const;
        Tuple operator+(const Tuple& t) const;
        Tuple operator-(const Tuple& t) const;
        Tuple operator-() const;
        Tuple operator*(float s) const;
        Tuple operator*(const Tuple& t) const;
        Tuple operator/(float s) const;
        Tuple& operator+=(const Tuple& t);
        Tuple& operator-=(const Tuple& t);
        float& operator[](size_t i);
        const float& operator[](size_t i) const;

        [[nodiscard]] Tuple reflect(const Tuple& n) const;
    };
    static_assert(sizeof(Tuple) == sizeof(float) * 4, "Tuple size mismatch");

    inline Tuple operator*(const float s, const Tuple& t) { return t * s; }
    std::ostream& operator<<(std::ostream& os, const Tuple& t);

    Tuple tuple(float x, float y, float z, float w);
    Tuple point(float x, float y, float z);
    Tuple vector(float x, float y, float z);
    Tuple color(float r, float g, float b);

    [[nodiscard]] float magnitude(const Tuple& t);
    [[nodiscard]] float dot(const Tuple& a, const Tuple& b);
    [[nodiscard]] Tuple normalize(const Tuple& t);
    [[nodiscard]] Tuple cross(const Tuple& a, const Tuple& b);

    using Point = Tuple;
    using Vector = Tuple;
    using Color = Tuple;
}
// rtc

#endif //RTC_TUPLE_H