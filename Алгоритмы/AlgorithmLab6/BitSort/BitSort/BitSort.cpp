#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

bool Sort(int* mas, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (mas[i] > mas[i + 1]) {
            return false;
        }
    }
    return true;
}

void bitwiseRadixSortRecursive(std::vector<int>& arr, int l, int r, int k) {
    if (l >= r || k < 0) return;

    int i = l, j = r;
    int mask = 1 << k;

    while (i <= j) {
        while (i <= j && !(arr[i] & mask)) i++;
        while (i <= j && (arr[j] & mask)) j--;
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
        bitwiseRadixSortRecursive(arr, l, j, k - 1);
        bitwiseRadixSortRecursive(arr, i, r, k - 1);
}

void bitwiseRadixSort(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int numBits = 0;
    while ((1 << numBits) <= maxVal) numBits++;
    bitwiseRadixSortRecursive(arr, 0, arr.size() - 1, numBits - 1);
}

void RandMas(int* mas, int n, int a, int b) {
    for (int i = 0; i < n; i++) {
        mas[i] = rand() % (b - a + 1) + a;
    }
}

int main() {
    srand(time(0));
    int numArrays = 3;
    int arraySize = 10;
    int minVal = -100;
    int maxVal = 200;
    int numRuns = 3;

    for (int i = 0; i < numArrays; ++i) {
        int* c_arr = new int[arraySize];
        RandMas(c_arr, arraySize, minVal, maxVal);

        std::vector<int> arr(c_arr, c_arr + arraySize);
        delete[] c_arr;

        int minArrVal = *std::min_element(arr.begin(), arr.end());
        if (minArrVal < 0) {
            for (int& x : arr) x -= minArrVal;
        }

        auto startTime = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < numRuns; ++j) {
            std::vector<int> arrCopy = arr;
            bitwiseRadixSort(arrCopy);
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        std::cout << "Original array: ";
        for (int x : arr) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "Average sort time: " << (double)duration.count() / numRuns << " microseconds" << std::endl;

        std::vector<int> arrCopy = arr;
        bitwiseRadixSort(arrCopy);

        int* sorted_c_arr = new int[arraySize];
        for (size_t k = 0; k < arrCopy.size(); ++k) sorted_c_arr[k] = arrCopy[k];

        std::cout << "Sorted array: ";
        for (int x : arrCopy) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "Sorted: " << (Sort(sorted_c_arr, arraySize) ? "yes" : "no") << std::endl;
        delete[] sorted_c_arr;
    }
    return 0;
}

