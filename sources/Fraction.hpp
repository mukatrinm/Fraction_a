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

    friend std::istream& operator>>(std::istream& input, Fraction& frac);
    friend std::ostream& operator<<(std::ostream& output, const Fraction& frac);
    Fraction operator+(const Fraction& other) const;
    friend Fraction operator+(const Fraction& lhs, double rhs);
    friend Fraction operator+(double lhs, const Fraction& rhs);
    Fraction operator-(const Fraction& other) const;
    friend Fraction operator-(const Fraction& lhs, double rhs);
    friend Fraction operator-(double lhs, const Fraction& rhs);
    Fraction operator/(const Fraction& other) const;
    friend Fraction operator/(const Fraction& lhs, double rhs);
    friend Fraction operator/(double lhs, const Fraction& rhs);
    Fraction operator*(const Fraction& other) const;
    friend Fraction operator*(const Fraction& lhs, double rhs);
    friend Fraction operator*(double lhs, const Fraction& rhs);
    Fraction& operator++();    // pre-increment
    Fraction operator++(int);  // post-increment
    Fraction& operator--();    // pre-decrement
    Fraction operator--(int);  // post-decrement

    bool operator==(const Fraction& other) const;
    friend bool operator==(const Fraction& lhs, double rhs);
    friend bool operator==(double lhs, const Fraction& rhs);
    bool operator>(const Fraction& other) const;
    friend bool operator>(const Fraction& lhs, double rhs);
    friend bool operator>(double lhs, const Fraction& rhs);
    bool operator<(const Fraction& other) const;
    friend bool operator<(const Fraction& lhs, double rhs);
    friend bool operator<(double lhs, const Fraction& rhs);
    bool operator>=(const Fraction& other) const;
    friend bool operator>=(const Fraction& lhs, double rhs);
    friend bool operator>=(double lhs, const Fraction& rhs);
    bool operator<=(const Fraction& other) const;
    friend bool operator<=(const Fraction& lhs, double rhs);
    friend bool operator<=(double lhs, const Fraction& rhs);
};
}  // namespace ariel
