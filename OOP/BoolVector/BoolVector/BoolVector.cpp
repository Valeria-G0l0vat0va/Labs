#include <assert.h>
#include <utility>
#include "BoolVector.h"
#include <string.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>

BoolVector::BoolVector()
    : BoolVector(CellSize)
{
}

BoolVector::BoolVector(int length)
    : BoolVector(length, false)
{
}

BoolVector::BoolVector(int length, bool value)
    : m_bitCount(length)
{
    m_cellCount = m_bitCount / CellSize;
    if (m_bitCount % CellSize != 0)
    {
        m_cellCount++;
    }
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = 0;
        for (int j = 0; j < CellSize; j++)
        {
            if (value)
            {
                m_cells[i] |= (1 << j);
            }
        }
    }
}

BoolVector::BoolVector(const char* bits)
    : BoolVector(strlen(bits))
{
    for (int i = 0; i < m_bitCount; i++)
    {
        if (bits[i] == '1')
        {
            setBitValue(i, true);
        }
    }
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_cellCount = other.m_cellCount;
    m_bitCount = other.m_bitCount;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::~BoolVector()
{
    delete[] m_cells;
}

int BoolVector::length() const
{
    return m_bitCount;
}

int BoolVector::bitCount() const
{
    return m_bitCount;
}

void BoolVector::swap(BoolVector& other)
{
    std::swap(m_cells, other.m_cells);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_bitCount, other.m_bitCount);
}

void BoolVector::invert()
{
    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = ~m_cells[i];
    }
}

bool BoolVector::bitValue(int index) const
{
    assert(index >= 0 && index < m_bitCount);
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
    assert(index >= 0 && index < m_bitCount);
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    if (value)
    {
        m_cells[index / CellSize] |= mask;
    }
    else
    {
        m_cells[index / CellSize] &= ~mask;
    }
}

void BoolVector::invertBit(int index) {
    assert(index >= 0 && index < m_bitCount);
    setBitValue(index, !bitValue(index));
}

void BoolVector::setBit(int index, bool value) {
    setBitValue(index, value);
}

void BoolVector::setBits(int start, int count, bool value) {
    assert(start >= 0 && start + count <= m_bitCount);
    for (int i = start; i < start + count; ++i) {
        setBitValue(i, value);
    }
}

void BoolVector::setAllBits(bool value) {
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] = value ? ~0 : 0;
    }
}

int BoolVector::weight() const
{
    int weight = 0;
    for (int i = 0; i < m_cellCount; i++)
    {
        for (int j = 0; j < CellSize; j++)
        {
            if (m_cells[i] & (1 << j))
            {
                weight++;
            }
        }
    }
    return weight;
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
    assert(m_bitCount == other.m_bitCount);

    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = m_cells[i] & other.m_cells[i];
    }
    return result;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
    assert(m_bitCount == other.m_bitCount);

    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] &= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
    assert(m_bitCount == other.m_bitCount);

    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = m_cells[i] | other.m_cells[i];
    }
    return result;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
    assert(m_bitCount == other.m_bitCount);

    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] |= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    assert(m_bitCount == other.m_bitCount);

    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = m_cells[i] ^ other.m_cells[i];
    }
    return result;
}

BoolVector& BoolVector::operator^=(const BoolVector& other)
{
    assert(m_bitCount == other.m_bitCount);

    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] ^= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator<<(int shift) const
{
    assert(shift >= 0);

    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = m_cells[i] << shift;
    }
    return result;
}

BoolVector BoolVector::operator>>(int shift) const
{
    assert(shift >= 0);

    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = m_cells[i] >> shift;
    }
    return result;
}

BoolVector& BoolVector::operator<<=(int shift)
{
    assert(shift >= 0);

    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] <<= shift;
    }
    return *this;
}

BoolVector& BoolVector::operator>>=(int shift)
{
    assert(shift >= 0);

    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] >>= shift;
    }
    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector result(m_bitCount);
    for (int i = 0; i < m_cellCount; i++)
    {
        result.m_cells[i] = ~m_cells[i];
    }
    return result;
}


BoolVector& BoolVector::operator=(const BoolVector& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] m_cells;

    m_bitCount = other.m_bitCount;
    m_cellCount = other.m_cellCount;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = other.m_cells[i];
    }
    return *this;
}

BoolVector::Rank BoolVector::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return Rank(&m_cells[index / CellSize], _mask(index));
}

int BoolVector::_excessRankCount() const
{
    return (m_cellCount * CellSize - m_length);
}

BoolVector::Cell BoolVector::_mask(int index)
{
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    return mask;
}

BoolVector::Rank::Rank(Cell* cell, Cell mask)
    : m_cell(cell)
    , m_mask(mask)
{
    assert(m_cell != nullptr);
    assert(m_mask > 0);
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank& other)
{
    return operator=(static_cast<bool>(other));
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value)
{
    if (value)
    {
        *m_cell |= m_mask;
    }
    else
    {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank::operator bool() const
{
    return (*m_cell & m_mask) != 0;
}




std::ostream& operator<<(std::ostream& stream, const BoolVector& bv)
{
    for (int i = 0; i < bv.bitCount(); ++i)
    {
        if (bv.bitValue(i))
            stream << "1";
        else
            stream << "0";
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, BoolVector& bv)
{
    std::string input;
    stream >> input;
    if (input.length() != bv.bitCount()) {
        std::cerr << "Ошибка: Длина строки не совпадает с количеством битов в BoolVector." << std::endl;
        return stream;
    }
    for (int i = 0; i < bv.bitCount(); ++i)
    {
        if (input[i] == '1') {
            bv.setBitValue(i, true);
        }
        else if (input[i] == '0') {
            bv.setBitValue(i, false);
        }
        else {
            std::cerr << "Ошибка: В строке найден недопустимый символ." << std::endl;
            return stream;
        }
    }
    return stream;
}
