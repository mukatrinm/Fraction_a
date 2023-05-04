#include "Fraction.hpp"

#include <math.h>

#include <numeric>
#include <valarray>

using namespace ariel;
using namespace std;

// https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
Fraction::Fraction(double number) {
    // make sure number has 3 digits after the decimal point.
    double abs_rounded = std::round(std::abs(number) * 1000.0) / 1000.0;
    number = std::copysign(abs_rounded, number);

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
    } else if (denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }

    int frac_gcd = gcd(numerator_, denominator_);
    numerator_ /= frac_gcd;
    denominator_ /= frac_gcd;
}

int Fraction::getNumerator() const {
    return numerator_;
}

int Fraction::getDenominator() const {
    return denominator_;
}

std::istream& ariel::operator>>(std::istream& input, Fraction& frac) {
    int numerator = 0;
    int denominator = 0;

    input >> numerator >> denominator;
    if (input.fail()) {
        throw runtime_error("input failed");
    }

    if (denominator == 0) {
        throw runtime_error("denominator can't be zero");
    }

    frac.numerator_ = numerator;
    frac.denominator_ = denominator;

    if (denominator < 0) {
        frac.numerator_ *= -1;
        frac.denominator_ *= -1;
    }

    return input;
}

std::ostream& ariel::operator<<(std::ostream& output, const Fraction& frac) {
    output << frac.numerator_ << "/" << frac.denominator_;
    return output;
}

/*************************
 * Arithmetic Operations *
 *************************/

Fraction Fraction::operator+(const Fraction& other) const {
    Fraction::checkOverflow('+', Fraction(numerator_, denominator_), other);

    int numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    int denominator = denominator_ * other.denominator_;
    int frac_gcd = gcd(numerator, denominator);

    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator+(const Fraction& lhs, double rhs) {
    Fraction::checkOverflow('+', lhs, Fraction(rhs));
    return lhs + Fraction(rhs);
}

Fraction ariel::operator+(double lhs, const Fraction& rhs) {
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

Fraction ariel::operator-(const Fraction& lhs, double rhs) {
    Fraction::checkOverflow('-', lhs, Fraction(rhs));
    return lhs - Fraction(rhs);
}

Fraction ariel::operator-(double lhs, const Fraction& rhs) {
    Fraction::checkOverflow('-', Fraction(lhs), rhs);
    return Fraction(lhs) - rhs;
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator_ == 0) {
        throw runtime_error("can't devide by zero");
    }

    Fraction::checkOverflow('/', Fraction(numerator_, denominator_), other);
    int numerator = numerator_ * other.denominator_;
    int denominator = denominator_ * other.numerator_;
    int frac_gcd = gcd(numerator, denominator);
    return Fraction{numerator / frac_gcd, denominator / frac_gcd};
}

Fraction ariel::operator/(const Fraction& lhs, double rhs) {
    Fraction::checkOverflow('/', lhs, Fraction(rhs));
    return lhs / Fraction(rhs);
}

Fraction ariel::operator/(double lhs, const Fraction& rhs) {
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

Fraction ariel::operator*(const Fraction& lhs, double rhs) {
    Fraction::checkOverflow('*', lhs, Fraction(rhs));
    return lhs * Fraction(rhs);
}

Fraction ariel::operator*(double lhs, const Fraction& rhs) {
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

bool ariel::operator==(const Fraction& lhs, double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(rhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, rhs);
    return Fraction::FractionToDouble(lhs) == num_3_percision;
}

bool ariel::operator==(double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(lhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, lhs);
    return num_3_percision == Fraction::FractionToDouble(rhs);
}

bool Fraction::operator>(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) > FractionToDouble(other);
}

bool ariel::operator>(const Fraction& lhs, double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(rhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, rhs);
    return Fraction::FractionToDouble(lhs) > num_3_percision;
}

bool ariel::operator>(double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(lhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, lhs);
    return num_3_percision > Fraction::FractionToDouble(rhs);
}

bool Fraction::operator>=(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) >= FractionToDouble(other);
}

bool ariel::operator>=(const Fraction& lhs, double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(rhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, rhs);
    return Fraction::FractionToDouble(lhs) >= num_3_percision;
}

bool ariel::operator>=(double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(lhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, lhs);
    return num_3_percision >= Fraction::FractionToDouble(rhs);
}

bool Fraction::operator<(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) < FractionToDouble(other);
}

bool ariel::operator<(const Fraction& lhs, double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(rhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, rhs);
    return Fraction::FractionToDouble(lhs) < num_3_percision;
}

bool ariel::operator<(double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(lhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, lhs);
    return num_3_percision < Fraction::FractionToDouble(rhs);
}

bool Fraction::operator<=(const Fraction& other) const {
    return FractionToDouble(Fraction(numerator_, denominator_)) <= FractionToDouble(other);
}

bool ariel::operator<=(const Fraction& lhs, double rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(rhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, rhs);
    return Fraction::FractionToDouble(lhs) <= num_3_percision;
}

bool ariel::operator<=(double lhs, const Fraction& rhs) {
    // make sure rhs has only 3 digits after decimal point
    double abs_rounded = std::round(std::abs(lhs) * 1000.0) / 1000.0;
    double num_3_percision = std::copysign(abs_rounded, lhs);
    return num_3_percision <= Fraction::FractionToDouble(rhs);
}

/*********************
 * Utility Functions *
 *********************/

double Fraction::FractionToDouble(const Fraction& frac) {
    double num = frac.getNumerator() / static_cast<double>(frac.getDenominator());

    double abs_rounded = std::round(std::abs(num) * 1000.0) / 1000.0;
    return std::copysign(abs_rounded, num);
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
