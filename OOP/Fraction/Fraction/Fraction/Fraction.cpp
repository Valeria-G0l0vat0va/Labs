#include "Fraction.h"    

Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю");
    }
    reduce();
}

Fraction Fraction::sum(const Fraction& b) const {
    return Fraction(numerator * b.denominator + b.numerator * denominator, denominator * b.denominator);
}

Fraction Fraction::sub(const Fraction& b) const {
    return Fraction(numerator * b.denominator - b.numerator * denominator, denominator * b.denominator);
}

Fraction Fraction::mul(const Fraction& b) const {
    return Fraction(numerator * b.numerator, denominator * b.denominator);
}

Fraction Fraction::div(const Fraction& b) const {
    if (b.numerator == 0) {
        std::cerr << "Fraction::div: error: b.numerator is 0, result will be 0/1.";
        return Fraction(0, 1);
    }
    return Fraction(numerator * b.denominator, denominator * b.numerator);
}

bool Fraction::operator==(const Fraction& b) const {
    return numerator * b.denominator == b.numerator * denominator;
}

bool Fraction::operator!=(const Fraction& b) const {
    return !(*this == b);
}

bool Fraction::operator>(const Fraction& b) const {
    return numerator * b.denominator > b.numerator * denominator;
}

bool Fraction::operator<(const Fraction& b) const {
    return numerator * b.denominator < b.numerator * denominator;
}

std::ostream& operator<<(std::ostream& stream, const Fraction& fraction) {
    return stream << fraction.numerator << "/" << fraction.denominator;
}

std::istream& operator>>(std::istream& stream, Fraction& fraction) {
    char slash;
    return stream >> fraction.numerator >> slash >> fraction.denominator;
}

int Fraction::gcd(int a, int b) const {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void Fraction::reduce() {
    if (denominator == 0) return;
    int gcd_val = Fraction::gcd(numerator, denominator); 
    numerator /= gcd_val;
    denominator /= gcd_val;
}

Fraction Fraction::randomFraction(int maxNumerator, int maxDenominator) {
    int numerator = rand() % maxNumerator + 1;
    int denominator = rand() % maxDenominator + 1;
    return Fraction(numerator, denominator);
}

Fraction Fraction::fromDouble(double value, int precision) {
    if (precision <= 0) {
        std::cerr << "Fraction::fromDouble: error: precision must be positive." << std::endl;
        return Fraction(0, 1); 
    }
    int integerPart = floor(value);
    double fractionalPart = value - integerPart;
    long multiplier = pow(10, precision); 
    long numerator = round(fractionalPart * multiplier);
    long denominator = multiplier;
    return Fraction(integerPart * denominator + numerator, denominator);
}

bool Fraction::isReducible() const {
    Fraction temp = *this; 
    return temp.gcd(temp.numerator, temp.denominator) != 1;
}