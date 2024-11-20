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

    void reduce();

    static Fraction fromDouble(double value, int precision);

    static Fraction randomFraction(int maxNumerator = 10, int maxDenominator = 10);

    bool isReducible() const;

private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const;
};

Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    if (denominator != 0) reduce();
    else {
        std::cerr << "Error: Denominator cannot be zero" << std::endl;
    }
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

void Fraction::reduce() {
    int common = gcd(numerator, denominator);
    numerator /= common;
    denominator /= common;
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

int Fraction::gcd(int a, int b) const {
    if (b == 0) return a;
    return gcd(b, a % b);
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
    long long multiplier = pow(10, precision); 
    long long numerator = round(fractionalPart * multiplier);
    long long denominator = multiplier;
    return Fraction(integerPart * denominator + numerator, denominator);
}


bool Fraction::isReducible() const {
    Fraction temp = *this; 
    return temp.gcd(temp.numerator, temp.denominator) != 1;
}


int main() {
    srand(time(0));
    Fraction f1 = Fraction::randomFraction(100,100); 
    Fraction f2 = Fraction::randomFraction(100,100); 

    std::cout << "f1: " << f1 << std::endl; 
    std::cout << "f2: " << f2 << std::endl; 

    Fraction sum = f1.sum(f2);
    std::cout << "f1 + f2: " << sum << std::endl;

    Fraction difference = f1.sub(f2);
    std::cout << "f1 - f2: " << difference << std::endl;

    Fraction product = f1.mul(f2);
    std::cout << "f1 * f2: " << product << std::endl;
    
    Fraction quotient = f1.div(f2);
    std::cout << "f1 / f2: " << quotient << std::endl;

    Fraction fromDouble = Fraction::fromDouble(0.8766546, 2);
    std::cout << "fromDouble: " << fromDouble << std::endl;

    if (f1.isReducible()) {
        std::cout << "Fraction f1 can be reduced" << std::endl;
    }
    else {
        std::cout << "Fraction f1 cannot be reduced" << std::endl;
    }

    if (f2.isReducible()) {
        std::cout << "Fraction f2 can be reduced" << std::endl;
    }
    else {
        std::cout << "Fraction f2 cannot be reduced" << std::endl;
    }

    return 0;
}