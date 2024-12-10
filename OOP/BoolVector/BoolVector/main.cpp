#include "BoolVector.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>



int main()
{
    srand(time(0));
    {
        BoolVector dummy(20, 1);
        for (int i = 0; i < dummy.length(); ++i)
        {
            std::cout << (dummy << i) << "\n";
        }
        for (int i = 0; i < dummy.length(); ++i)
        {
            std::cout << (dummy >> i) << "\n";
        }
    }

    BoolVector bv("101011000001");
    std::cout << "bv: " << bv << " , weight = " << bv.weight() << std::endl;

    // ������� ������ �� ������ �����
    BoolVector bv1("101011001110");
    std::cout << "bv1: " << bv1 << " , weight = " << bv1.weight() << std::endl;

    // ������� ������ ������ 12, ����������� ������
    BoolVector bv2(12);
    std::cout << "bv2: " << bv2 << " , weight = " << bv2.weight() << std::endl;

    // ������� ����� ������� bv
    BoolVector bv3 = ~bv;
    std::cout << "bv3: " << bv3 << " , weight = " << bv3.weight() << std::endl;

    // ������������� �������� ����� � bv1
    bv1.setBitValue(1, true);
    bv1.setBitValue(6, true);
    std::cout << "bv1: " << bv1 << std::endl;

    std::cout << "��� 3: " << bv[3] << std::endl;
    std::cout << "��� 7: " << bv[7] << std::endl;

    // ��������� ��������� ���������
    BoolVector bv4 = bv1 & bv3;
    std::cout << "bv1 & bv3: " << bv4 << std::endl;

    // ��������� ��������� ��������
    BoolVector bv5 = bv1 | bv3;
    std::cout << "bv1 | bv3: " << bv5 << std::endl;

    // ��������� ��������� ����������� ���
    BoolVector bv6 = bv1 ^ bv3;
    std::cout << "bv1 ^ bv3: " << bv6 << std::endl;

    // ��������� ����� �����
    BoolVector bv7 = bv1 << 2;
    std::cout << "bv1 << 2: " << bv7 << std::endl;

    // ��������� ����� ������
    BoolVector bv8 = bv1 >> 2;
    std::cout << "bv1 >> 2: " << bv8 << std::endl;

    // ��������� ��������� ��������
    BoolVector bv9 = ~bv2;
    std::cout << "bv9: " << bv9 << std::endl;

    BoolVector bv10 = bv1 &= bv2;
    std::cout << "bv10: " << bv10 << std::endl;

    BoolVector bv11 = bv1 |= bv;
    std::cout << "bv11: " << bv11 << std::endl;

    BoolVector bv12 = bv ^= bv1;
    std::cout << "bv12: " << bv12 << std::endl;

    BoolVector bv13 = bv1 <<= 3;
    std::cout << "bv13: " << bv13 << std::endl;

    BoolVector bv14 = bv1 >>= 3;
    std::cout << "bv14: " << bv14 << std::endl;

    BoolVector bv15 = bv3;
    std::cout << "bv15: " << bv15 << std::endl;

    return 0;
}