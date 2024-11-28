#include <iostream>
#include <string>
#include <vector>

int findFirst(const std::string& text, const std::string& pattern) {
    for (size_t i = 0; i <= text.length() - pattern.length(); ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern.length(); ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

std::vector<int> findAll(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    for (size_t i = 0; i <= text.length() - pattern.length(); ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern.length(); ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) positions.push_back(i);
    }
    return positions;
}

std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int start, int end) {
    std::vector<int> positions;
    if (start < 0 || end >= text.length() || start > end) return positions;
    for (size_t i = start; i <= end - pattern.length(); ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern.length(); ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) positions.push_back(i);
    }
    return positions;
}

int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string pattern = "tor";

    std::cout << "First occurrence: " << findFirst(text, pattern) << std::endl; 

    std::vector<int> allOccurrences = findAll(text, pattern);
    std::cout << "All occurrences: ";
    for (int index : allOccurrences) std::cout << index << " "; 
    std::cout << std::endl;

    std::vector<int> occurrencesInRange = findAllInRange(text, pattern, 17, 91);
    std::cout << "Occurrences in range (17-91): ";
    for (int index : occurrencesInRange) std::cout << index << " "; 
    std::cout << std::endl;

    std::vector<int> occurrencesInRange2 = findAllInRange(text, pattern, 28, 36);
    std::cout << "Occurrences in range (28-36): ";
    for (int index : occurrencesInRange2) std::cout << index << " "; 
    std::cout << std::endl;

    return 0;
}