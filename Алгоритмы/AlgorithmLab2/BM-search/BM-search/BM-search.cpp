#include <iostream>
#include <string>
#include <vector>

void Tab(const std::string& p, int TAB[256]) {
    int m = p.length();
    for (int i = 0; i < 256; i++) {
        TAB[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        TAB[p[i]] = m - 1 - i;
    }
}

int BM_search(const std::string& s, const std::string& p) {
    int n = s.length();
    int m = p.length();
    if (m == 0) return 0;
    if (n < m) return -1; 

    int TAB[256];
    Tab(p, TAB);

    int i = m - 1;
    int j = m - 1;
    while (i < n) {
        int k = i;
        j = m - 1;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) {
            return k + 1; 
        }
        i += TAB[s[i]]; 
    }
    return -1; 
}

std::vector<int> BM_search_all(const std::string& s, const std::string& p) {
    std::vector<int> index;
    int n = s.length();
    int m = p.length();
    if (m == 0) return index; 
    if (n < m) return index; 

    int TAB[256];
    Tab(p, TAB);

    int i = m - 1;
    while (i < n) {
        int k = i;
        int j = m - 1;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) {
            index.push_back(k + 1);
            i += m; 
        }
        else {
            i += TAB[s[i]]; 
        }
    }
    return index; 
}

std::vector<int> BM_search_range(const std::string& s, const std::string& p, int start, int end) {
    std::vector<int> index;
    int n = s.length();
    int m = p.length();
    if (m == 0 || start < 0 || end < start || end >= n) return index; 

    int TAB[256];
    Tab(p, TAB);

    int i = start + m - 1;
    while (i <= end) {
        int k = i;
        int j = m - 1;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) {
            index.push_back(k + 1); 
            i += m; 
        }
        else {
            i += TAB[s[i]]; 
        }
    }
    return index; 
}

int main() {
    std::string text = "Mom was washing the frame. The grass was cleaned up this morning";
    std::string pattern = "was";

    int firstIndex = BM_search(text, pattern);
    std::cout << "First occurrence index: " << firstIndex << std::endl;

    std::vector<int> allIndices = BM_search_all(text, pattern);
    std::cout << "All occurrence indices: ";
    for (int index : allIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    std::vector<int> rangeIndices = BM_search_range(text, pattern, 15, 40);
    std::cout << "Occurrence indices in range: ";
    for (int index : rangeIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}
