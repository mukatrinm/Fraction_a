#include <limits>

#include "doctest.h"
#include "sources/Fraction.hpp"

using namespace ariel;

/**
 * if we run out of cards, we turn our collected cards face down , shufflle and continue playing.
 *
 * identical cards of same rank (war), we play 1 cards facedown staggered on top of the face-up card
 * then each plaver flips one card face-up
 * * the player with the higher rank wins all the cards in the war including the facedown
 * * if they tie again, another ward
 * * if the player doesn't have cards to place down because they ran out of cards in their deck and discard then they lose
 *   the war the first player to collect all the cards in the deck wins.
 */

TEST_CASE("Object Initialization") {
    Fraction a(5, 3), b(5.1);

    CHECK_EQ(a.getNumerator(), 5);
    CHECK_EQ(a.getDenominator(), 3);

    CHECK_EQ(b.getNumerator(), 51);
    CHECK_EQ(b.getDenominator(), 10);
}

TEST_CASE("Exceptions Test") {
    Fraction a(5, 3);

    SUBCASE("Initialization") {
        CHECK_THROWS(Fraction{1, 0});
    }

    SUBCASE("Division by zero") {
        CHECK_THROWS(a / Fraction{0});
        CHECK_THROWS(a / 0);
    }

    SUBCASE("Overflow/Underflow") {
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();

        Fraction a(max_int, 1);
        Fraction b(min_int, 1);

        CHECK_THROWS(a + 1);
        CHECK_THROWS(b - 1);
    }
}

TEST_CASE("Arithmetic Operations") {
    Fraction a(5, 3), b(14, 21), c(5.1);
    Fraction d(-1), e(-1, 2);
    Fraction op_frac;

    SUBCASE("Addition") {
        op_frac = a + b;
        CHECK_EQ(op_frac.getNumerator(), 7);
        CHECK_EQ(op_frac.getDenominator(), 3);

        op_frac = a + c;
        CHECK_EQ(op_frac.getNumerator(), 203);
        CHECK_EQ(op_frac.getDenominator(), 30);

        op_frac = a + Fraction{0};
        CHECK_EQ(op_frac.getNumerator(), 5);
        CHECK_EQ(op_frac.getDenominator(), 3);

        op_frac = d + e;
        CHECK_EQ(op_frac.getNumerator(), -3);
        CHECK_EQ(op_frac.getDenominator(), 2);
    }

    SUBCASE("Subtraction") {
        op_frac = a - b;
        CHECK_EQ(op_frac.getNumerator(), 1);
        CHECK_EQ(op_frac.getDenominator(), 1);

        op_frac = a - c;
        CHECK_EQ(op_frac.getNumerator(), -103);
        CHECK_EQ(op_frac.getDenominator(), 30);

        op_frac = a - Fraction{0};
        CHECK_EQ(op_frac.getNumerator(), 5);
        CHECK_EQ(op_frac.getDenominator(), 3);

        op_frac = Fraction{0} - a;
        CHECK_EQ(op_frac.getNumerator(), -5);
        CHECK_EQ(op_frac.getDenominator(), 3);

        op_frac = d - e;
        CHECK_EQ(op_frac.getNumerator(), -1);
        CHECK_EQ(op_frac.getDenominator(), 2);
    }

    SUBCASE("Multiplication") {
        op_frac = a * b;
        CHECK_EQ(op_frac.getNumerator(), 10);
        CHECK_EQ(op_frac.getDenominator(), 9);

        op_frac = a * c;
        CHECK_EQ(op_frac.getNumerator(), 17);
        CHECK_EQ(op_frac.getDenominator(), 2);

        op_frac = a * Fraction{0};
        CHECK_EQ(op_frac.getNumerator(), 0);
        CHECK_EQ(op_frac.getDenominator(), 1);

        op_frac = Fraction{-1} * a;
        CHECK_EQ(op_frac.getNumerator(), -5);
        CHECK_EQ(op_frac.getDenominator(), 3);
    }

    SUBCASE("Division") {
        op_frac = a / b;
        CHECK_EQ(op_frac.getNumerator(), 5);
        CHECK_EQ(op_frac.getDenominator(), 2);

        op_frac = a / c;
        CHECK_EQ(op_frac.getNumerator(), 50);
        CHECK_EQ(op_frac.getDenominator(), 153);

        op_frac = Fraction{0} / a;
        CHECK_EQ(op_frac.getNumerator(), 0);
        CHECK_EQ(op_frac.getDenominator(), 1);

        op_frac = Fraction{-1} / a;
        CHECK_EQ(op_frac.getNumerator(), -3);
        CHECK_EQ(op_frac.getDenominator(), 5);

        op_frac = -1 / a;
        CHECK_EQ(op_frac.getNumerator(), -3);
        CHECK_EQ(op_frac.getDenominator(), 5);
    }

    SUBCASE("prefix/postfix increment/decrerment") {
        op_frac = a++;
        CHECK_EQ(op_frac.getNumerator(), 5);
        CHECK_EQ(op_frac.getDenominator(), 3);

        CHECK_EQ(a.getNumerator(), 8);
        CHECK_EQ(a.getDenominator(), 3);

        op_frac = a--;
        CHECK_EQ(op_frac.getNumerator(), 8);
        CHECK_EQ(op_frac.getDenominator(), 3);

        CHECK_EQ(a.getNumerator(), 5);
        CHECK_EQ(a.getDenominator(), 3);

        op_frac = ++a;
        CHECK_EQ(op_frac.getNumerator(), 8);
        CHECK_EQ(op_frac.getDenominator(), 3);

        CHECK_EQ(a.getNumerator(), 8);
        CHECK_EQ(a.getDenominator(), 3);

        op_frac = --a;
        CHECK_EQ(op_frac.getNumerator(), 5);
        CHECK_EQ(op_frac.getDenominator(), 3);

        CHECK_EQ(a.getNumerator(), 5);
        CHECK_EQ(a.getDenominator(), 3);
    }
}

TEST_CASE("Comparison Operations") {
    Fraction a(5, 3), b(14, 21), c(-1.1), d(-1);
    Fraction op_frac;

    SUBCASE("Greater") {
        CHECK(a > b);
        CHECK(a > c);
        CHECK(d > c);
        CHECK(a > 0);
        CHECK(1 > b);
    }

    SUBCASE("Greater Equals") {
        CHECK(a >= b);
        CHECK(a >= 1);
        CHECK(1 >= b);
        CHECK(a >= c);
        CHECK(d >= c);
        CHECK(a >= a);
    }

    SUBCASE("Less") {
        CHECK(b < a);
        CHECK(c < a);
        CHECK(c < d);
        CHECK(a < 10);
        CHECK(-1 < b);
    }

    SUBCASE("Less Equals") {
        CHECK(b <= a);
        CHECK(c <= a);
        CHECK(c <= d);
        CHECK_FALSE(a <= b);
    }

    SUBCASE("Equals") {
        CHECK(a == a);
        CHECK_FALSE(a == b);
        CHECK_FALSE(a == 5 / 3);
    }
}
