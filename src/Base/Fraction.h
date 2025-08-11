//
// Created by Administrator on 2025/8/11.
//

#ifndef FRACTION_H
#define FRACTION_H
#include <cstdint>
#include <numeric>
namespace FCT
{
    struct Fraction {
        int32_t numerator;
        int32_t denominator;

        Fraction() noexcept : numerator(1), denominator(1) {}
        Fraction(int32_t num) noexcept : numerator(num), denominator(1) {}
        Fraction(int32_t num, int32_t den) noexcept : numerator(num), denominator(den) {
            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
            simplify();
        }

        void simplify() noexcept {
            if (numerator == 0) {
                denominator = 1;
                return;
            }
            int32_t gcd = std::gcd(std::abs(numerator), std::abs(denominator));
            numerator /= gcd;
            denominator /= gcd;
        }

        Fraction operator*(const Fraction& other) const noexcept {
            return Fraction(numerator * other.numerator, denominator * other.denominator);
        }

        Fraction operator/(const Fraction& other) const noexcept {
            return Fraction(numerator * other.denominator, denominator * other.numerator);
        }

        bool operator==(const Fraction& other) const noexcept {
            return numerator * other.denominator == other.numerator * denominator;
        }

        bool operator!=(const Fraction& other) const noexcept {
            return !(*this == other);
        }

        float toFloat() const noexcept {
            return static_cast<float>(numerator) / static_cast<float>(denominator);
        }

        bool isUnit() const noexcept {
            return numerator == denominator && numerator > 0;
        }
    };
}
#endif //FRACTION_H
