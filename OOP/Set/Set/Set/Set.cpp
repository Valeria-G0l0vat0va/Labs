#include "Set.h"

Set::Set() : size(256) {
    data = new bool[size];
    for (size_t i = 0; i < size; ++i) data[i] = false;
}

Set::Set(size_t maxSize) : size(maxSize) {
    data = new bool[size];
    for (size_t i = 0; i < size; ++i) data[i] = false;
}

Set::Set(const char* arr) : Set(256) {
    for (size_t i = 0; arr[i] != '\0'; ++i) {
        add(arr[i]);
    }
}

Set::Set(const Set& other) : size(other.size) {
    data = new bool[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Set::~Set() {
    delete[] data;
}

bool Set::contains(char c) const {
    return (c >= 0 && c < size) && data[c];
}

size_t Set::getCardinality() const {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i]) {
            count++;
        }
    }
    return count;
}

void Set::add(char c) {
    if (c >= 0 && c < size) {
        data[c] = true;
    }
    else {
        std::cerr << "Warning: Character out of range." << std::endl;
    }
}

Set& Set::operator=(const Set& other) {
    for (int i = 0; i < 256; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

bool Set::operator==(const Set& other) const {
    for (int i = 0; i < 256; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

Set Set::operator|(const Set& other) const {
    Set result;
    for (int i = 0; i < 256; ++i) {
        result.data[i] = data[i] || other.data[i];
    }
    return result;
}

Set Set::operator&(const Set& other) const {
    Set result;
    for (int i = 0; i < 256; ++i) {
        result.data[i] = data[i] && other.data[i];
    }
    return result;
}

Set Set::operator/(const Set& other) const {
    Set result;
    for (int i = 0; i < 256; ++i) {
        result.data[i] = data[i] && !other.data[i];
    }
    return result;
}

Set Set::operator~() const {
    Set result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = !data[i];
    }
    return result;
}

Set Set::operator+(char c) const {
    Set result = *this;
    result.add(c);
    return result;
}

void Set::print() const {
    std::cout << "{";
    bool first = true;
    for (size_t i = 0; i < size; ++i) {
        if (data[i]) { 
            if (!first) std::cout << ", ";
            std::cout << (char)i;
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

void Set::input() {
    char c;
    while (std::cin.get(c) && c != '\n') {  
        add(c);
    }
}
