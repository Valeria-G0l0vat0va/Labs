#include "Set.h"
#include <string> 

Set::Set() : BoolVector(256) {}

Set::Set(size_t maxSize) : BoolVector(maxSize) {}

Set::Set(const char* arr) : Set(256) {
    for (size_t i = 0; arr[i] != '\0'; ++i) {
        add(arr[i]);
    }
}

Set::Set(const Set& other) : BoolVector(other) {}

Set::~Set() {}

bool Set::contains(char element) const {
    return getBitValue(element);
}

void Set::add(char element) {
    if (element >= 0 && element < length() && !contains(element)) {
        setBitValue(element, true);
    }
}

void Set::remove(char element) {
    if (contains(element)) {
        setBitValue(element, false);
    }
}

size_t Set::cardinality() const {
    size_t count = 0;
    for (size_t i = 0; i < 256; ++i) {
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
    if (length() != other.length()) 
        return false;
    for (int i = 0; i < length(); ++i) {
        if (getBitValue(i) != other.getBitValue(i)) 
            return false;
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

Set& Set::operator|=(const Set& other) {
    size_t maxLength = std::max(length(), other.length());
    for (size_t i = 0; i < maxLength; ++i) {
        if (i < other.length() && other.getBitValue(i)) {
            setBitValue(i, true);
        }
    }
    return *this;
}


Set Set::operator&(const Set& other) const {
    size_t maxLength = std::max(length(), other.length());
    Set result(maxLength);
    for (size_t i = 0; i < maxLength; ++i) {
        bool thisBit = false;
        if (i < length()) {
            thisBit = getBitValue(i);
        }
        bool otherBit = false;
        if (i < other.length()) {
            otherBit = other.getBitValue(i);
        }
        if (thisBit && otherBit) {
            result.setBitValue(i, true);
        }
    }
    return result;
}

Set& Set::operator&=(const Set& other) {
    size_t maxLength = std::max(length(), other.length());
    for (size_t i = 0; i < maxLength; ++i) {
        bool thisBit = false;
        if (i < length()) {
            thisBit = getBitValue(i);
        }
        bool otherBit = false;
        if (i < other.length()) {
            otherBit = other.getBitValue(i);
        }
        if (!(thisBit && otherBit)) {
            setBitValue(i, false);
        }
    }
    return *this;
}

Set Set::operator/(const Set& other) const {
    Set result(length());
    for (size_t i = 0; i < length(); ++i) {
        bool thisBit = false;
        if (i < length()) {
            thisBit = getBitValue(i);
        }
        bool otherBit = false;
        if (i < other.length()) {
            otherBit = other.getBitValue(i);
        }
        if (thisBit && !otherBit) {
            result.setBitValue(i, true);
        }
    }
    return result;
}

Set& Set::operator/=(const Set& other) {
    for (size_t i = 0; i < length(); ++i) {
        if (i < other.length() && other.getBitValue(i)) {
            setBitValue(i, false);
        }
    }
    return *this;
}

Set Set::operator~() const {
    Set result(length());
    for (size_t i = 0; i < length(); ++i) {
        if (!getBitValue(i)) {
            result.add(i);
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

Set Set::operator-(const Set& other) const {
    size_t maxLength = std::max(length(), other.length());
    Set result(maxLength);

    for (size_t i = 0; i < maxLength; ++i) {
        bool thisBit = false;
        if (i < length()) {
            thisBit = getBitValue(i);
        }
        bool otherBit = false;
        if (i < other.length()) {
            otherBit = other.getBitValue(i);
        }
        if (thisBit && !otherBit) {
            result.setBitValue(i, true);
        }
    }
    return result;
}

Set& Set::operator-=(char element) {
    remove(element);
    return *this;
}


std::istream& operator>>(std::istream& stream, Set& bs) {
    for (size_t i = 0; i < bs.length(); ++i) {
        bs.setBitValue(i, false); 
    }
    char c;
    while (stream.get(c)) { 
        if (c == '\n') break; 
        if (c >= 0 && c < bs.length()) {
            bs.add(c);
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& os, const Set& other) {
    os << "{ ";
    for (size_t i = 0; i < other.length(); ++i) {
        if (other.getBitValue(i)) {
            os << static_cast<int>(i) << " ";
        }
    }
    os << "}";
    return os;
}