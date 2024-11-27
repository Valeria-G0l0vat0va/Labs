#pragma once
#include<iostream>

class Array
{
public:
    typedef int* iterator;
    typedef int value_type;
    typedef int& reference;
    typedef int* pointer;
    typedef int difference_type;

public:
    Array(int size = 10);
    Array(const Array& other);
    Array(Array&& other);
    ~Array();

    int size() const;

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;
    int find(const int& value) const;
    void sort();

    bool insert(const int index, const int& value);
    bool removeAt(const int index);
    bool remove(const int& value);
    void removeAll(const int& value);
    int& max();
    int& min();
    const int& max() const;
    const int& min() const;
    bool insert_before(iterator pos, const int& value);
    bool remove_range(iterator start, iterator end);
    void swap(Array& other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    int& operator[](int index);
    const int& operator[](int index) const;
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

private:
    int* m_array = nullptr;
    int m_size = 0;
};
std::ostream& operator<<(std::ostream& os, const Array& arr);
std::istream& operator>>(std::istream& is, Array& arr);
