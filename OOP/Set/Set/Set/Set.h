#pragma once
#include"../../../BoolVector/BoolVector/BoolVector.h"
#include <iostream>


class Set {

private:
    bool* data;
    size_t size;

public:
    Set();
    Set(size_t maxSize);
    Set(const char* arr);
    Set(const Set& other);
    ~Set();
    void add(char c);
    bool contains(char c) const;
    size_t getCardinality() const;

    Set& operator=(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;
    Set operator|(const Set& other) const;
    Set operator&(const Set& other) const;
    Set operator/(const Set& other) const;
    Set operator~() const;
    Set operator+(char c) const;
    void print() const;
    void input();
};