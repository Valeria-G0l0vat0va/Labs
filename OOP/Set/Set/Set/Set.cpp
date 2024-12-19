#include "Set.h"

Set::Set() : BoolVector(256) {}

Set::Set(size_t maxSize) : BoolVector(maxSize) {}

Set::Set(const char* arr) : Set(256) {
    for (size_t i = 0; arr[i] != '\0'; ++i) {
        add(arr[i]);
    }
}

Set::Set(const Set& other) : BoolVector(other) {}

Set::~Set() {}

int Set::contains(char c) const {
    if (c < 0 || c >= length()) {
        throw std::out_of_range("Character out of range for this set.");
    }
    return getBitValue(c);
}

size_t Set::getCardinality() const {
    size_t count = 0;
    for (int i = 0; i < length(); ++i) {
        if (getBitValue(i)) {
            count++;
        }
    }
    return count;
}

void Set::add(char c) {
    if (c < 0 || c >= length()) {
        throw std::out_of_range("Character out of range for this set.");
    }
    setBitValue(c, true);
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        BoolVector::operator=(other); 
    }
    return *this;
}

bool Set::operator==(const Set& other) const {
    if (length() != other.length()) return false;
    for (int i = 0; i < length(); ++i) {
        if (getBitValue(i) != other.getBitValue(i)) return false;
    }
    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

Set Set::operator|(const Set& other) const {
    Set result(std::max(length(), other.length()));
    for (int i = 0; i < result.length(); ++i) {
        result.setBitValue(i, getBitValue(i) || other.getBitValue(i));
    }
    return result;
}

Set Set::operator&(const Set& other) const {
    Set result(std::max(length(), other.length()));
    for (int i = 0; i < result.length(); ++i) {
        result.setBitValue(i, getBitValue(i) && other.getBitValue(i));
    }
    return result;
}

Set Set::operator/(const Set& other) const {
    Set result(length());
    for (int i = 0; i < length(); ++i) {
        result.setBitValue(i, getBitValue(i) && !other.getBitValue(i));
    }
    return result;
}

Set Set::operator~() const {
    Set result(length());
    for (int i = 0; i < length(); ++i) {
        result.setBitValue(i, !getBitValue(i));
    }
    return result;
}

Set Set::operator+(char c) const {
    Set result = *this;
    result.add(c);
    return result;
}

void Set::print() const {
    std::cout << "{ ";
    for (size_t i = 0; i < length(); ++i) {
        if (getBitValue(i)) {
            std::cout << i << " ";
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
