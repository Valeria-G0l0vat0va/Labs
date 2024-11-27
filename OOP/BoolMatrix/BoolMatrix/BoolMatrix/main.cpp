#include "BoolMatrix.h"

int main() {
    const char* data[] = { "1011", "0101", "1010" };

    BoolMatrix matrix1(3, 4, true);
    BoolMatrix matrix2(3, 4, false);
    BoolMatrix matrix3(data, 3, 4);
    BoolMatrix matrix4 = matrix1;

    std::cout << "Matrix 1:\n" << matrix1 << std::endl;
    std::cout << "Matrix 2:\n" << matrix2 << std::endl;
    std::cout << "Matrix 3:\n" << matrix3 << std::endl;

    std::cout << "Matrix 4 (copy):\n" << matrix4 << std::endl;

    std::cout << "Weight of matrix1: " << matrix1.weight() << std::endl;
    std::cout << "Weight of row 1 in matrix1: " << matrix1.rowWeight(0) << std::endl; 
    matrix1.invertComponent(1, 2);
    std::cout << "Matrix 1 after inversion:\n" << matrix1 << std::endl;

    matrix1.invertComponents(0, 1, 2);
    std::cout << "Matrix 1 after multiple inversions:\n" << matrix1 << std::endl;

    matrix1.setComponent(0, 0, false);
    std::cout << "Matrix 1 after setting component to false:\n" << matrix1 << std::endl;

    matrix1.setComponents(1, 0, 3, true);
    std::cout << "Matrix 1 after setting multiple components to true:\n" << matrix1 << std::endl;

    BoolMatrix matrix5 = matrix1 & matrix3;
    std::cout << "Matrix 1 & Matrix 3:\n" << matrix5 << std::endl;

    BoolMatrix matrix6 = matrix1 | matrix3;
    std::cout << "Matrix 1 | Matrix 3:\n" << matrix6 << std::endl;

    BoolMatrix matrix7 = matrix1 ^ matrix3;
    std::cout << "Matrix 1 ^ Matrix 3:\n" << matrix7 << std::endl;

    BoolMatrix matrix8 = ~matrix1;
    std::cout << "~Matrix 1:\n" << matrix8 << std::endl;

    return 0;
}