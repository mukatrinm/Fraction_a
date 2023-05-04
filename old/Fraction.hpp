#pragma once

#include <iostream>

namespace ariel {
class Fraction {
   private:
    int numerator_;
    int denominator_;

    static Fraction doubleToFraction(const double num);

   public:
    Fraction(int numerator);
    Fraction(int numerator, int denominator);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    Fraction operator+(Fraction& other);
    // friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
    // friend Fraction operator+(const Fraction& lhs, const float rhs);
    // friend Fraction operator+(const float lhs, const Fraction& rhs);
    friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
    // friend Fraction operator-(const Fraction& lhs, const float rhs);
    // friend Fraction operator-(const float lhs, const Fraction& rhs);
    friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);
    // friend Fraction operator/(const Fraction& lhs, const float rhs);
    // friend Fraction operator/(const float lhs, const Fraction& rhs);
    friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator*(const Fraction& lhs, const double rhs);
    friend Fraction operator*(const double lhs, const Fraction& rhs);
    Fraction& operator++();    // pre-increment
    Fraction operator++(int);  // post-increment
    Fraction& operator--();    // pre-decrement
    Fraction operator--(int);  // post-decrement

    // bool operator==(const Fraction& other) const;
};
}  // namespace ariel
