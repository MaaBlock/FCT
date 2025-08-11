//
// Created by Administrator on 2025/8/11.
//

#ifndef FRACTIONSCALE2D_H
#define FRACTIONSCALE2D_H
#include "./Fraction.h"
namespace FCT
{
    struct FractionScale2D {
        Fraction width;
        Fraction height;

        FractionScale2D() noexcept : width(1), height(1) {}
        FractionScale2D(const Fraction& w, const Fraction& h) noexcept : width(w), height(h) {}
        FractionScale2D(const Fraction& uniform) noexcept : width(uniform), height(uniform) {}

        FractionScale2D operator*(const FractionScale2D& other) const noexcept {
            return FractionScale2D(width * other.width, height * other.height);
        }

        FractionScale2D operator/(const FractionScale2D& other) const noexcept {
            return FractionScale2D(width / other.width, height / other.height);
        }

        bool operator==(const FractionScale2D& other) const noexcept {
            return width == other.width && height == other.height;
        }

        bool operator!=(const FractionScale2D& other) const noexcept {
            return !(*this == other);
        }

        bool isUnit() const noexcept {
            return width.isUnit() && height.isUnit();
        }
    };
}
#endif //FRACTIONSCALE2D_H
