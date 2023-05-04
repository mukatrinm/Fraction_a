#include "Fraction.hpp"

using namespace ariel;

Fraction::Fraction(int numerator) : numerator_{numerator}, denominator_{1} {
}

Fraction::Fraction(int numerator, int denominator) : numerator_{numerator}, denominator_{denominator} {
}

Fraction Fraction::operator+(Fraction& other) {
    int numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    int denominator = denominator_ * other.denominator_;
    return Fraction{numerator, denominator};
}

// Fraction ariel::Fraction::operator+(Fraction& other) const {
//     return Fraction();
// }

std::ostream& ariel::operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator_ << "/" << f.denominator_;
    return os;
}

// // a/b + c/d = (a*d + b*c)/(b*d)
// Fraction ariel::operator+(const Fraction& lhs, const Fraction& rhs) {
//     return Fraction(1, 1);
// }

// Fraction ariel::operator-(const Fraction& lhs, const Fraction& rhs) {
//     return Fraction(1, 1);
// }

// Fraction ariel::operator/(const Fraction& lhs, const Fraction& rhs) {
//     return Fraction(1, 1);
// }

// Fraction ariel::operator*(const Fraction& lhs, const Fraction& rhs) {
//     return Fraction(1, 1);
// }

// Fraction ariel::operator*(const float& lhs, const Fraction& rhs) {
//     return Fraction(1, 1);
// }

// Fraction ariel::operator*(const Fraction& lhs, const float& rhs) {
//     return Fraction(1, 1);
// }

Fraction& Fraction::operator++() {
    numerator_ *= 2;
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction temp(*this);
    ++(*this);
    return temp;
}

Fraction& Fraction::operator--() {
    numerator_ -= numerator_;
    return *this;
}

Fraction Fraction::operator--(int) {
    Fraction temp(*this);
    --(*this);
    return temp;
}

// a/b + c/d = (a*d + b*c)/(b*d)
// Fraction ariel::operator+(const Fraction& lhs, const Fraction& rhs) {
//     int numerator = lhs.numerator_ * rhs.denominator_ + rhs.numerator_ * lhs.denominator_;
//     int denominator = lhs.denominator_ * rhs.denominator_;
//     return Fraction{numerator, denominator};
// }

// a/b - c/d = (a*d - b*c)/(b*d)
Fraction ariel::operator-(const Fraction& lhs, const Fraction& rhs) {
    int numerator = lhs.numerator_ * rhs.denominator_ - rhs.numerator_ * lhs.denominator_;
    int denominator = lhs.denominator_ * rhs.denominator_;
    return Fraction{numerator, denominator};
}

// // a/b - c/d = (a*d - b*c)/(b*d)
// Fraction ariel::operator-(const Fraction& lhs, const Fraction& rhs) {
//     int numerator = lhs.numerator_ * rhs.denominator_ - rhs.numerator_ * lhs.denominator_;
//     int denominator = lhs.denominator_ * rhs.denominator_;
//     return Fraction{numerator, denominator};
// }

Fraction ariel::operator/(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(1, 1);
}

Fraction ariel::operator*(const Fraction& lhs, const Fraction& rhs) {
    int numerator = lhs.numerator_ * rhs.numerator_;
    int denominator = lhs.denominator_ * rhs.denominator_;
    return Fraction{numerator, denominator};
}

Fraction ariel::operator*(const Fraction& lhs, const double rhs) {
    int numerator = lhs.numerator_ * static_cast<int>(rhs);
    Fraction temp = Fraction::doubleToFraction(rhs);
    return lhs * temp;
}

Fraction ariel::operator*(const double lhs, const Fraction& rhs) {
    return rhs * lhs;
}

Fraction ariel::Fraction::doubleToFraction(const double num) {
    int numerator = static_cast<int>(num);
    Fraction frac = Fraction{static_cast<int>(num)} + Fraction{numerator, 1000};
    return frac;
}
