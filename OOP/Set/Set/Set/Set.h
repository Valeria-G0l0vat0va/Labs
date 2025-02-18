#pragma once
#include"../../../BoolVector/BoolVector/BoolVector.h"
#include <iostream>
#include<algorithm>
#include <stdexcept>


class Set : public BoolVector {

private:
public:
    Set();
    Set(size_t maxSize);
    Set(const char* arr);
    Set(const Set& other);
    ~Set();
    void add(char c);
    void remove(char element);
    bool contains(char element) const;
    size_t cardinality() const;

    Set& operator=(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;
    Set operator|(const Set& other) const;
    Set& operator|=(const Set& other);
    Set operator&(const Set& other) const;
    Set& operator&=(const Set& other);
    Set operator/(const Set& other) const;
    Set& operator/=(const Set& other);
    Set operator~() const;
    Set operator+(char c) const;
    Set& operator+=(char element);
    Set operator-(char element) const;
    Set& operator-=(char element);

    static const int start = 31;
    static const int end = 128;
    static const int charSize = end - start;
};
std::ostream& operator<<(std::ostream& stream, const Set& s);
std::istream& operator>>(std::istream& stream, Set& s);
