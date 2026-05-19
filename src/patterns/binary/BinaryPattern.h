//
// Created by Nicholas Solomon on 2026-05-17.
//

#ifndef RTC_BINARYPATTERN_H
#define RTC_BINARYPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::binary {
    struct BinaryPattern : Pattern {
        std::unique_ptr<Pattern> a = nullptr;
        std::unique_ptr<Pattern> b = nullptr;

        BinaryPattern() = default;
        BinaryPattern(const BinaryPattern& other) : Pattern(other), a(other.a ? other.a->clone() : nullptr), b(other.b ? other.b->clone() : nullptr) {}
        BinaryPattern(std::unique_ptr<Pattern> a, std::unique_ptr<Pattern> b) { this->a = std::move(a); this->b = std::move(b); transform = Matrix::identity(); }
        BinaryPattern& operator=(const BinaryPattern& other) {
            if (this != &other) {
                Pattern::operator=(other);
                a = other.a ? other.a->clone() : nullptr;
                b = other.b ? other.b->clone() : nullptr;
            }
            return *this;
        }
        BinaryPattern(BinaryPattern&&) = default;
        BinaryPattern& operator=(BinaryPattern&&) = default;
        [[nodiscard]] Color color_at(const Point& point) const override = 0;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override = 0;
    };
}

#endif //RTC_BINARYPATTERN_H