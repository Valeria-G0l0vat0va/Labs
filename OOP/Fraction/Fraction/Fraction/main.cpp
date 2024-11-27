#include "Fraction.h"    

int main() {
    srand(time(0));
    Fraction f1 = Fraction::randomFraction(100, 100);
    Fraction f2 = Fraction::randomFraction(100, 100);

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