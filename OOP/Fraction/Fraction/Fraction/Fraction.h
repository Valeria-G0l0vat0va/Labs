#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <ctime> 
#include <cassert> 

class Fraction {
public:
    Fraction();
    Fraction(int numerator, int denominator);
    ~Fraction() = default;

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    void setNumerator(int value) { numerator = value; }
    void setDenominator(int value) {
        if (value == 0) {
            std::cerr << "Fraction::setDenominator: error: value is 0, won't assign.";
            return;
        }
        denominator = value;
    }

    Fraction sum(const Fraction& b) const;
    Fraction sub(const Fraction& b) const;
    Fraction mul(const Fraction& b) const;
    Fraction div(const Fraction& b) const;

    bool operator==(const Fraction& b) const;
    bool operator!=(const Fraction& b) const;
    bool operator>(const Fraction& b) const;
    bool operator<(const Fraction& b) const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& stream, Fraction& fraction);

    void reduce();

    static Fraction fromDouble(double value, int precision);

    static Fraction randomFraction(int maxNumerator = 10, int maxDenominator = 10);

    bool isReducible() const;

private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const;
};