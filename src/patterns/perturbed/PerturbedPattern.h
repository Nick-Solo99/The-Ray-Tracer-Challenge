//
// Created by Nicholas Solomon on 2026-05-19.
//

#ifndef RTC_PERTURBEDPATTERN_H
#define RTC_PERTURBEDPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::perturbed {
    struct PerturbedPattern final : Pattern {
        std::unique_ptr<Pattern> pattern;
        PerturbedPattern() = default;
        explicit PerturbedPattern(std::unique_ptr<Pattern> pattern) : pattern(std::move(pattern)) {}
        PerturbedPattern(const PerturbedPattern& other) : Pattern(other), pattern(other.pattern ? other.pattern->clone() : nullptr) {}
        PerturbedPattern& operator=(const PerturbedPattern& other) {
            if (this != &other) {
            Pattern::operator=(other);
            pattern = other.pattern ? other.pattern->clone() : nullptr;
            }
            return *this;
        }
        PerturbedPattern(PerturbedPattern&&) = default;
        PerturbedPattern& operator=(PerturbedPattern&&) = default;
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };
}

#endif //RTC_PERTURBEDPATTERN_H