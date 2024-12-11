#include "BoolMatrix.h"

BoolMatrix::BoolMatrix() : BoolMatrix(0, 0) {}

BoolMatrix::BoolMatrix(int rows, int cols) : m_rows(rows), m_cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }
    m_matrix = new BoolVector [m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = BoolVector(m_cols);
    }
}

BoolMatrix::BoolMatrix(int rows, int cols, bool value) : m_rows(rows), m_cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }
    m_matrix = new BoolVector[m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = BoolVector(m_cols, value);
    }
}

BoolMatrix::BoolMatrix(const char** charMatrix, int rows, int cols) : m_rows(rows), m_cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }
    m_matrix = new BoolVector [m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = BoolVector(m_cols);
        for (int j = 0; j < m_cols; ++j) {
            if (charMatrix[i][j] == '1') {
                m_matrix[i].setBitValue(j, true);
            }
            else if (charMatrix[i][j] != '0') {
                throw std::invalid_argument("Invalid character in char matrix");
            }
        }
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix& other) : m_rows(other.m_rows), m_cols(other.m_cols) {
    m_matrix = new BoolVector [m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = other.m_matrix[i];
    }
}

BoolMatrix::~BoolMatrix() {
    delete[] m_matrix;
}

int BoolMatrix::getRows() const 
{
    return m_rows; 
}
int BoolMatrix::getCols() const 
{ 
    return m_cols;
}

BoolVector& BoolMatrix::operator[](int row) {
    if (row < 0 || row >= getRows()) {  
        throw std::out_of_range("Row index out of bounds");
    }
    return m_matrix[row];
}

const BoolVector& BoolMatrix::operator[](int row) const {
    if (row < 0 || row >= getRows()) {  
        throw std::out_of_range("Row index out of bounds");
    }
    return m_matrix[row];
}

int BoolMatrix::weight() const {
    int count = 0;
    for (int i = 0; i < m_rows; i++) {
        count += m_matrix[i].weight();
    }
    return count;
}

BoolVector BoolMatrix::conjunction() const {
    if (m_rows == 0) return BoolVector(0);
    BoolVector result = m_matrix[0];
    for (int i = 1; i < m_rows; ++i) {
        result &= m_matrix[i]; 
    }
    return result;
}


BoolVector BoolMatrix::disjunction() const {
    if (m_rows == 0) return BoolVector(0);
    BoolVector result = m_matrix[0];
    for (int i = 1; i < m_rows; ++i) {
        result |= m_matrix[i]; 
    }
    return result;
}
int BoolMatrix::rowWeight(int row) const {
    checkBounds(row, 0);
    return m_matrix[row].weight();
}

void BoolMatrix::checkBounds(int row, int col) const {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        throw std::out_of_range("Index out of bounds");
    }
}

void BoolMatrix::invertComponent(int row, int col) {
    checkBounds(row, col);
    m_matrix[row].invertBit(col);
}

void BoolMatrix::invertComponents(int row, int start, int count) {
    checkBounds(row, start);
    if (start + count > m_cols) throw std::out_of_range("Index out of bounds");
    for (int i = 0; i < count; ++i) {
        m_matrix[row].invertBit(start + i);
    }
}

void BoolMatrix::setComponent(int row, int col, bool value) {
    checkBounds(row, col);
    m_matrix[row].setBit(col, value);
}

void BoolMatrix::setComponents(int row, int start, int count, bool value) {
    checkBounds(row, start);
    if (start + count > m_cols) throw std::out_of_range("Index out of bounds");
    for (int i = 0; i < count; ++i) {
        m_matrix[row].setBit(start + i, value);
    }
}

bool BoolMatrix::get(int row, int col) const {
    checkBounds(row, col);
    return m_matrix[row][col];
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other) {
    if (this != &other) {
        delete[] m_matrix;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_matrix = new BoolVector[m_rows];
        for (int i = 0; i < m_rows; ++i) {
            m_matrix[i] = BoolVector(other.m_matrix[i]);
        }
    }
    return *this;
}
void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_matrix, other.m_matrix);
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) 
        throw std::invalid_argument("Matrices must have the same dimensions");
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] &= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) 
        throw std::invalid_argument("Matrices must have the same dimensions");
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] |= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) 
        throw std::invalid_argument("Matrices must have the same dimensions");
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] ^= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator~() const {
    BoolMatrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        result[i] = ~m_matrix[i]; 
    }
    return result;
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for & operation");
    }
    BoolMatrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        result[i] = (m_matrix[i]) & (other.m_matrix[i]);
    }
    return result;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for | operation");
    }
    BoolMatrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        result[i] = (m_matrix[i]) | (other.m_matrix[i]);
    }
    return result;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for ^ operation");
    }
    BoolMatrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        result[i] = (m_matrix[i]) ^ (other.m_matrix[i]);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) { 
        for (int j = 0; j < matrix.getCols(); ++j) { 
            os << matrix.get(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& matrix) {
    int rows, cols;
    is >> rows >> cols;
    if (is.fail() || rows <= 0 || cols <= 0) 
        return is;

    matrix = BoolMatrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            is >> value;
            if (is.fail()) return is; 
            matrix[i].setBit(j, value != 0);
        }
    }
    return is;
}