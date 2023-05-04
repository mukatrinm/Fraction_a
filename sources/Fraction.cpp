#include "Fraction.hpp"

#include <math.h>

#include <numeric>

using namespace ariel;
using namespace std;
#include <valarray>

// https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
// TODO: add overflow checks
Fraction::Fraction(double number) {
    int cycles = 10;
    double precision = 5e-4;
    int sign = number > 0 ? 1 : -1;
    number = number * sign;  // abs(number);
    double new_number = NAN, whole_part = NAN;
    double decimal_part = number - (int)number;
    int counter = 0;

    valarray<double> vec_1{double((int)number), 1}, vec_2{1, 0}, temporary;

    while (decimal_part > precision & counter < cycles) {
        new_number = 1 / decimal_part;
        whole_part = (int)new_number;

        temporary = vec_1;
        vec_1 = whole_part * vec_1 + vec_2;
        vec_2 = temporary;

        decimal_part = new_number - whole_part;
        counter += 1;
    }

    numerator_ = sign * static_cast<int>(vec_1[0]);
    denominator_ = static_cast<int>(vec_1[1]);
}

Fraction::Fraction(int numerator, int denominator) : numerator_{numerator}, denominator_{denominator} {
    if (denominator_ == 0) {
        throw invalid_argument("denominator can't be zero");
    }
}

int Fraction::getNumerator() const {
    return numerator_;
}

int Fraction::getDenominator() const {
    return denominator_;
}

std::ostream& ariel::operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator_ << "/" << f.denominator_;
    return os;
}

/*************************
 * Arithmetic Operations *
 *************************/

Fraction Fraction::operator+(const Fraction& other) const {
    int numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    int denominator = denominator_ * other.denominator_;
    int frac_gcd = gcd(numerator, denominator);

    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator+(const Fraction& lhs, const double rhs) {
    Fraction::checkOverflow('+', lhs, Fraction(rhs));
    return lhs + Fraction(rhs);
}

Fraction ariel::operator+(const double lhs, const Fraction& rhs) {
    Fraction::checkOverflow('+', Fraction(lhs), rhs);
    return Fraction(lhs) + rhs;
}

Fraction Fraction::operator-(const Fraction& other) const {
    Fraction::checkOverflow('-', Fraction(numerator_, denominator_), other);
    int numerator = numerator_ * other.denominator_ - other.numerator_ * denominator_;
    int denominator = denominator_ * other.denominator_;
    int frac_gcd = gcd(numerator, denominator);

    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator-(const Fraction& lhs, const double rhs) {
    Fraction::checkOverflow('-', lhs, Fraction(rhs));
    return lhs - Fraction(rhs);
}

Fraction ariel::operator-(const double lhs, const Fraction& rhs) {
    Fraction::checkOverflow('-', Fraction(lhs), rhs);
    return Fraction(lhs) - rhs;
}

Fraction Fraction::operator/(const Fraction& other) const {
    Fraction::checkOverflow('/', Fraction(numerator_, denominator_), other);
    int numerator = numerator_ * other.denominator_;
    int denominator = denominator_ * other.numerator_;
    int frac_gcd = gcd(numerator, denominator);
    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator/(const Fraction& lhs, const double rhs) {
    Fraction::checkOverflow('/', lhs, Fraction(rhs));
    return lhs / Fraction(rhs);
}

Fraction ariel::operator/(const double lhs, const Fraction& rhs) {
    Fraction::checkOverflow('/', Fraction(lhs), rhs);
    return Fraction(lhs) / rhs;
}

Fraction Fraction::operator*(const Fraction& other) const {
    Fraction::checkOverflow('*', Fraction(numerator_, denominator_), other);
    int numerator = numerator_ * other.numerator_;
    int denominator = denominator_ * other.denominator_;
    int frac_gcd = gcd(numerator, denominator);

    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator*(const Fraction& lhs, const double rhs) {
    Fraction::checkOverflow('*', lhs, Fraction(rhs));
    return lhs * Fraction(rhs);
}

Fraction ariel::operator*(const double lhs, const Fraction& rhs) {
    Fraction::checkOverflow('*', Fraction(lhs), rhs);
    return Fraction(lhs) * rhs;
}

Fraction& Fraction::operator++() {
    Fraction::checkOverflow('+', Fraction(numerator_, denominator_), Fraction(1));
    numerator_ += denominator_;
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction::checkOverflow('+', Fraction(numerator_, denominator_), Fraction(1));
    Fraction temp(*this);
    ++(*this);
    return temp;
}

Fraction& Fraction::operator--() {
    Fraction::checkOverflow('-', Fraction(numerator_, denominator_), Fraction(1));
    numerator_ -= denominator_;
    return *this;
}

Fraction Fraction::operator--(int) {
    Fraction::checkOverflow('-', Fraction(numerator_, denominator_), Fraction(1));
    Fraction temp(*this);
    --(*this);
    return temp;
}

/*************************
 * Comparison Operations *
 *************************/

bool Fraction::operator==(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) == FractionToDouble(other);
}

bool Fraction::operator>(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) > FractionToDouble(other);
}

bool ariel::operator>(const Fraction& lhs, const double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((rhs - trunc(rhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(rhs) + frac_part;
    return Fraction::FractionToDouble(lhs) > num_3_percision;
}

bool ariel::operator>(const double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((lhs - trunc(lhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(lhs) + frac_part;
    return num_3_percision > Fraction::FractionToDouble(rhs);
}

bool Fraction::operator>=(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) >= FractionToDouble(other);
}

bool ariel::operator>=(const Fraction& lhs, const double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((rhs - trunc(rhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(rhs) + frac_part;
    return Fraction::FractionToDouble(lhs) >= num_3_percision;
}

bool ariel::operator>=(const double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((lhs - trunc(lhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(lhs) + frac_part;
    return num_3_percision >= Fraction::FractionToDouble(rhs);
}

bool Fraction::operator<(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) < FractionToDouble(other);
}

bool ariel::operator<(const Fraction& lhs, const double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((rhs - trunc(rhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(rhs) + frac_part;
    return Fraction::FractionToDouble(lhs) < num_3_percision;
}

bool ariel::operator<(const double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((lhs - trunc(lhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(lhs) + frac_part;
    return num_3_percision < Fraction::FractionToDouble(rhs);
}

bool Fraction::operator<=(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) <= FractionToDouble(other);
}

bool ariel::operator<=(const Fraction& lhs, const double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((rhs - trunc(rhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(rhs) + frac_part;
    return Fraction::FractionToDouble(lhs) <= num_3_percision;
}

bool ariel::operator<=(const double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double frac_part = trunc((lhs - trunc(lhs)) * 1000) / 1000.0;
    double num_3_percision = static_cast<int>(lhs) + frac_part;
    return num_3_percision <= Fraction::FractionToDouble(rhs);
}

/*********************
 * Utility Functions *
 *********************/

double Fraction::FractionToDouble(const Fraction& frac) {
    double num = frac.getNumerator() / static_cast<double>(frac.getDenominator());
    double frac_part = trunc((num - trunc(num)) * 1000) / 1000.0;
    return static_cast<int>(num) + frac_part;
}

// check for overflow
// https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
void Fraction::checkOverflow(char opt, const Fraction& lhs, const Fraction& rhs) {
    int res1 = 0, res2 = 0, res3 = 0;
    switch (opt) {
        case '+':
            if (__builtin_mul_overflow(lhs.getNumerator(), rhs.getDenominator(), &res1) ||
                __builtin_mul_overflow(rhs.getNumerator(), lhs.getDenominator(), &res2) ||
                __builtin_mul_overflow(lhs.getDenominator(), rhs.getDenominator(), &res3) ||
                __builtin_add_overflow(res1, res2, &res3)) {
                throw std::overflow_error("overflow found");
            }
            break;
        case '-':
            if (__builtin_mul_overflow(lhs.getNumerator(), rhs.getDenominator(), &res1) ||
                __builtin_mul_overflow(rhs.getNumerator(), lhs.getDenominator(), &res2) ||
                __builtin_mul_overflow(lhs.getDenominator(), rhs.getDenominator(), &res3) ||
                __builtin_sub_overflow(res1, res2, &res3)) {
                throw std::overflow_error("overflow found");
            }
            break;
        case '*':
            if (__builtin_mul_overflow(lhs.getNumerator(), rhs.getNumerator(), &res1) ||
                __builtin_mul_overflow(lhs.getDenominator(), rhs.getDenominator(), &res2)) {
                throw std::overflow_error("overflow found");
            }
            break;
        case '/':
            if (__builtin_mul_overflow(lhs.getNumerator(), rhs.getDenominator(), &res1) ||
                __builtin_mul_overflow(lhs.getDenominator(), rhs.getNumerator(), &res2)) {
                throw std::overflow_error("overflow found");
            }
            break;

        default:
            throw std::invalid_argument("opt should be '+' or '-' or '*' or '/'");
            break;
    }
}
