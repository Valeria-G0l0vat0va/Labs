#include "Set.h"
#include <string> 

Set::Set() : BoolVector(charSize) {}

Set::Set(size_t maxSize) : BoolVector(maxSize) {}

Set::Set(const char* arr) : Set(charSize) {
    for (size_t i = 0; arr[i] != '\0'; ++i) {
        add(arr[i]);
    }
}

Set::Set(const Set& other) : BoolVector(other) {}

Set::~Set() {}

bool Set::contains(char element) const {
    if (element < start || element >= end) {
        throw std::out_of_range("Element out of range");
    }
    return getBitValue(element - start);
}

void Set::add(char element) {
    if (element < start || element >= end) {
        throw std::out_of_range("Element out of range");
    }
    setBitValue(element - start, true);
}

void Set::remove(char element) {
    if (contains(element)) {
        setBitValue(element - start, false);
    }
}

size_t Set::cardinality() const {
    size_t count = 0;
    for (size_t i = 0; i < charSize; ++i) {
        if (getBitValue(i)) {
            count++;
        }
    }
    return count;
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        BoolVector::operator=(other); 
    }
    return *this;
}

bool Set::operator==(const Set& other) const {
    for (size_t i = 0; i < charSize; i++) {
        if (getBitValue(i) != other.getBitValue(i)) {
            return false;
        }
    }
    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

Set Set::operator|(const Set& other) const {
    Set result = *this;
    result |= other;
    return result;
}

Set& Set::operator|=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        if (i < other.charSize) {
            setBitValue(i, getBitValue(i) || other.getBitValue(i));
        }
    }
    return *this;
}


Set Set::operator&(const Set& other) const {
    Set result = *this;
    result &= other;
    return result;
}

Set& Set::operator&=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        if (i < other.charSize) {
            setBitValue(i, getBitValue(i) && other.getBitValue(i));
        }
        else {
            setBitValue(i, false);
        }
    }
    return *this;
}

Set Set::operator/(const Set& other) const {
    Set result = *this;
    result /= other;
    return result;
}

Set& Set::operator/=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        if (i < other.charSize && other.getBitValue(i)) {
            setBitValue(i, false);
        }
    }
    return *this;
}

Set Set::operator~() const {
    Set result;
    for (size_t i = 0; i < charSize; ++i) {
        if (!getBitValue(i)) {
            result.add(static_cast<char>(i + start));
        }
    }
    return result;
}

Set Set::operator+(char c) const {
    return Set(*this) += c;
}


Set& Set::operator+=(char element) {
    add(element);
    return *this;
}

Set Set::operator-(char element) const {
    Set result = *this;
    result.remove(element);
    return result;
}

Set& Set::operator-=(char element) {
    remove(element);
    return *this;
}


std::istream& operator>>(std::istream& stream, Set& bs) {
    for (size_t i = 0; i < bs.charSize; ++i) {
        bs.setBitValue(i, false); 
    }
    char c;
    while (stream.get(c)) { 
        if (c == '\n') break; 
        if (c >= bs.start && c <= bs.end) {
            bs.add(c);
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& os, const Set& other) {
    os << "{ ";
    for (size_t i = 0; i < other.charSize; ++i) {
        if (other.getBitValue(i)) {
            os << static_cast<int>(i) << " ";
        }
    }
    os << "}";
    return os;
}

