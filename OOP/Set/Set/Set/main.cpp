#include "Set.h" 
#include <iostream>

int main() {
    Set set1("hello");
    Set set2("world");
    Set set3; 

    std::cout << "Введите символы для множества set3 (нажмите Enter для завершения): ";
    set3.input();

    std::cout<< "set1: ";
    set1.print();
    std::cout << "set2: ";
    set2.print();
    std::cout << "set3: ";
    set3.print();

    std::cout << "set1 | set2: ";
    (set1 | set2).print();
    std::cout << "set1 & set2: ";
    (set1 & set2).print();
    std::cout << "set1 / set2: ";
    (set1 / set2).print();
    std::cout << "~set1: ";
    (~set1).print();
    std::cout << "set1 + 'x': ";
    (set1 + 'x').print();
    std::cout << "set1 == set2: " << (set1 == set2) << std::endl;
    std::cout << "set1 != set2: " << (set1 != set2) << std::endl;
    std::cout << "Cardinality of set1: " << set1.getCardinality() << std::endl;

    return 0;
}

