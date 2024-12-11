#pragma once
#include "../../../BoolVector/BoolVector/BoolVector.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>



class BoolMatrix {
public:
    BoolMatrix();
    BoolMatrix(int rows, int cols);
    BoolMatrix(int rows, int cols, bool value);
    BoolMatrix(const char** charMatrix, int rows, int cols);
    BoolMatrix(const BoolMatrix& other);
    ~BoolMatrix();

    int getRows() const;
    int getCols() const;
    int weight() const;
    BoolVector conjunction() const;
    BoolVector disjunction() const;
    BoolVector& operator[](int row);
    const BoolVector& operator[](int row) const;
    int rowWeight(int row) const;
    void checkBounds(int row, int col) const;
    void invertComponent(int row, int col);
    void invertComponents(int row, int start, int count);
    void setComponent(int row, int col, bool value);
    void setComponents(int row, int start, int count, bool value);
    bool get(int row, int col) const;

    BoolMatrix& operator=(const BoolMatrix& other);
    BoolMatrix& operator&=(const BoolMatrix& other);
    BoolMatrix& operator|=(const BoolMatrix& other);
    BoolMatrix& operator^=(const BoolMatrix& other);
    BoolMatrix operator&(const BoolMatrix& other) const;
    BoolMatrix operator|(const BoolMatrix& other) const;
    BoolMatrix operator^(const BoolMatrix& other) const;
    BoolMatrix operator~() const;
    void swap(BoolMatrix& other); 



private:
    int m_rows;
    int m_cols;
    BoolVector* m_matrix = nullptr;
};
std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix);
std::istream& operator>>(std::istream& is, BoolMatrix& matrix);