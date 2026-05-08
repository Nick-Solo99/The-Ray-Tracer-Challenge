//
// Created by xGrim on 2026-05-07.
//

#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H


namespace rtc::tuples {

    struct Tuple {
        float x, y, z, w;

        [[nodiscard]] bool isPoint() const;
        [[nodiscard]] bool isVector() const;

        bool operator==(const Tuple& t) const;
        bool operator!=(const Tuple& t) const;
        Tuple operator+(const Tuple& t) const;
        Tuple operator-(const Tuple& t) const;
        Tuple operator-() const;
        Tuple operator*(float s) const;
        Tuple operator/(float s) const;
        Tuple& operator+=(const Tuple& t);
        Tuple& operator-=(const Tuple& t);
    };

    Tuple tuple(float x, float y, float z, float w);
    Tuple point(float x, float y, float z);
    Tuple vector(float x, float y, float z);

    float magnitude(const Tuple& t);
    float dot(const Tuple& a, const Tuple& b);
    Tuple normalize(const Tuple& t);
    Tuple cross(const Tuple& a, const Tuple& b);
}
// rtc

#endif //RTC_TUPLE_H