#pragma once

#include <iostream>

namespace ariel {
class Fraction {
   private:
    int numerator_;
    int denominator_;

   public:
    Fraction(double number = 0.0);
    Fraction(int numerator, int denominator);
    int getNumerator() const;
    int getDenominator() const;
    static double FractionToDouble(const Fraction& frac);
    static void checkOverflow(char opt, const Fraction& lhs, const Fraction& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    Fraction operator+(const Fraction& other) const;
    friend Fraction operator+(const Fraction& lhs, const double rhs);
    friend Fraction operator+(const double lhs, const Fraction& rhs);
    Fraction operator-(const Fraction& other) const;
    friend Fraction operator-(const Fraction& lhs, const double rhs);
    friend Fraction operator-(const double lhs, const Fraction& rhs);
    Fraction operator/(const Fraction& other) const;
    friend Fraction operator/(const Fraction& lhs, const double rhs);
    friend Fraction operator/(const double lhs, const Fraction& rhs);
    Fraction operator*(const Fraction& other) const;
    friend Fraction operator*(const Fraction& lhs, const double rhs);
    friend Fraction operator*(const double lhs, const Fraction& rhs);
    Fraction& operator++();    // pre-increment
    Fraction operator++(int);  // post-increment
    Fraction& operator--();    // pre-decrement
    Fraction operator--(int);  // post-decrement

    bool operator==(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    friend bool operator>(const Fraction& lhs, const double rhs);
    friend bool operator>(const double lhs, const Fraction& rhs);
    bool operator<(const Fraction& other) const;
    friend bool operator<(const Fraction& lhs, const double rhs);
    friend bool operator<(const double lhs, const Fraction& rhs);
    bool operator>=(const Fraction& other) const;
    friend bool operator>=(const Fraction& lhs, const double rhs);
    friend bool operator>=(const double lhs, const Fraction& rhs);
    bool operator<=(const Fraction& other) const;
    friend bool operator<=(const Fraction& lhs, const double rhs);
    friend bool operator<=(const double lhs, const Fraction& rhs);
};
}  // namespace ariel
