#include "array.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

Array::Array(int size)
{
    if (size < 0)
    {
        size = -size;
    }
    m_size = size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = int();
    }
}

Array::Array(const Array& other)
{
    m_size = other.m_size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}

Array::Array(Array&& other)
{
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_array = nullptr;
}

Array::~Array()
{
    delete[] m_array;
}

int Array::size() const
{
    return m_size;
}

Array::iterator Array::begin()
{
    return m_array;
}

Array::iterator Array::end()
{
    return m_array + m_size;
}

const Array::iterator Array::begin() const
{
    return m_array;
}

const Array::iterator Array::end() const
{
    return m_array + m_size;
}

int Array::find(const int& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] == value) return i;
    }
    return -1;
}

void Array::sort() {
    std::sort(begin(), end());
}

bool Array::insert(const int index, const int& value)
{
    if (index < 0 || index > m_size)
    {
        return false;
    }
    int* newArray = new int[m_size + 1];
    for (int i = 0; i < index; i++)
    {
        newArray[i] = m_array[i];
    }

    newArray[index] = value;

    for (int i = index + 1; i < m_size + 1; i++)
    {
        newArray[i] = m_array[i - 1];
    }

    delete[] m_array;
    m_array = newArray;
    m_size++;

    return true;
}

bool Array::removeAt(const int index) {
    if (index < 0 || index >= m_size) return false;

    int* newArray = new int[m_size - 1];
    for (int i = 0; i < index; ++i) newArray[i] = m_array[i];
    for (int i = index + 1; i < m_size; ++i) newArray[i - 1] = m_array[i];

    delete[] m_array;
    m_array = newArray;
    m_size--;
    return true;
}

bool Array::remove(const int& value) {
    int index = find(value);
    return removeAt(index);
}

void Array::removeAll(const int& value) {
    int index = find(value);
    while (index != -1) {
        removeAt(index);
        index = find(value);
    }
}

int& Array::max() {
    assert(m_size > 0);
    int* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

int& Array::min() {
    assert(m_size > 0);
    int* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

const int& Array::max() const {
    assert(m_size > 0);
    const int* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

const int& Array::min() const {
    assert(m_size > 0);
    const int* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

bool Array::insert_before(iterator pos, const int& value) {
    if (pos < begin() || pos > end()) return false;
    int index = pos - begin();
    return insert(index, value);
}

bool Array::remove_range(iterator start, iterator end) {
    if (start < begin() || end > this->end() || start >= end) return false;

    int numToRemove = end - start;
    int newSize = m_size - numToRemove;
    int* newArray = new int[newSize];

    int i = 0;
    for (iterator it = begin(); it < start; ++it) newArray[i++] = *it;
    for (iterator it = end; it < this->end(); ++it) newArray[i++] = *it;

    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
    return true;
}

void Array::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

Array& Array::operator=(const Array& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_size = other.m_size;
    delete[] m_array;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = other.m_array[i];
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_size = other.m_size;
    delete[] m_array;
    m_array = other.m_array;
    other.m_array = nullptr;
    return *this;
}

int& Array::operator[](int index)
{
    return m_array[index];
}

const int& Array::operator[](int index) const
{
    return m_array[index];
}

Array Array::operator+(const Array& other) const
{
    Array result(m_size + other.m_size); 
    int i = 0;
    for (; i < m_size; ++i) {
        result[i] = m_array[i];
    }
    for (int j = 0; j < other.m_size; ++j) {
        result[i + j] = other.m_array[j]; 
    }
    return result;
}

Array& Array::operator+=(const Array& other) {
    int newSize = m_size + other.m_size;
    int* newArray = new int[newSize];

    for (int i = 0; i < m_size; ++i) {
        newArray[i] = m_array[i];
    }
    for (int i = 0; i < other.m_size; ++i) {
        newArray[m_size + i] = other.m_array[i];
    }

    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
    return *this;
}

bool Array::operator==(const Array& other) const {
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; ++i)
        if (m_array[i] != other.m_array[i])
            return false;
    return true;
}

bool Array::operator!=(const Array& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "[";
    for (int i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i < arr.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Array& arr) {
    char c1, c2;
    is >> c1;  
    if (c1 != '[') return is; 
    is >> c2; 
    if (c2 != ']') return is; 
    return is;
}


