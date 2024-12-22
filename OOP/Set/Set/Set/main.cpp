#include "Set.h" 
#include <iostream>

int main() {
    Set set1("hello");
    Set set2("world");
    Set set3; 

    std::cout << "Enter the characters for the set3 set (press Enter to finish): ";
    std::cin>>set3;
    std::cout << set3 << std::endl;

    std::cout<< "set1: " << set1 << std::endl;
    std::cout << "set2: " << set2 << std::endl;
    std::cout << "set3: " << set3 << std::endl;

    std::cout << "set1 | set2: " << (set1 | set2) << std::endl;
    std::cout << "set1 & set2: " << (set1 & set2) << std::endl;
    std::cout << "set1 / set2: " << (set1 / set2) << std::endl;
    std::cout << "~set1: " << (~set1) << std::endl;
    std::cout << "set1 + 'x': " << (set1 + 'x') << std::endl;
    std::cout << "set1 == set2: " << (set1 == set2) << std::endl;
    std::cout << "set1 != set2: " << (set1 != set2) << std::endl;
    std::cout << "set1 - set3: " << (set1 - set3) << std::endl;
    std::cout << "Cardinality of set1: " << set1.cardinality() << std::endl;

    return 0;
}

