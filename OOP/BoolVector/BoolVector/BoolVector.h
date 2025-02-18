#pragma once

#include <iostream>

class BoolVector
{
public:
    using Cell = unsigned char;
    static const int CellSize = 8;
    BoolVector();
    BoolVector(const char* bits);
    BoolVector(int length);
    BoolVector(int length, bool value);
    BoolVector(const BoolVector& other);
    ~BoolVector();

    int length() const;
    int bitCount() const;

    void swap(BoolVector& other);
    void invert();

    bool operator[](int index) const;
    bool bitValue(int index) const;
    bool getBitValue(int index) const;
    void setBitValue(int index, bool value);
    void invertBit(int index);
    void setBit(int index, bool value);
    void setBits(int start, int count, bool value);
    void setAllBits(bool value);
    int weight() const;


    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);
    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);
    BoolVector operator<<(int shift) const;
    BoolVector operator>>(int shift) const;
    BoolVector& operator<<=(int shift);
    BoolVector& operator>>=(int shift);
    BoolVector operator~() const;
    BoolVector& operator=(const BoolVector& other);
private:
    Cell* m_cells = nullptr;
    int m_bitCount = 0;
    int m_cellCount = 0;
};
std::ostream& operator<<(std::ostream& stream, const BoolVector& bv);
std::istream& operator>>(std::istream& stream, BoolVector& bv);