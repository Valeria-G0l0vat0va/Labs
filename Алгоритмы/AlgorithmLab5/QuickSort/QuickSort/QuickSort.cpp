#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include<string>

void RandMas(std::vector<int>& mas, int a, int b) {
    for (int& element : mas) {
        element = rand() % (b - a + 1) + a;
    }
}

void hoarSort(std::vector<int>& mas, int l, int r) {
    if (l >= r) {
        return;
    }
    int i = l;
    int j = r;
    int x = mas[(l + r) / 2];
    while (i <= j) {
        while (mas[i] < x) {
            i++;
        }
        while (mas[j] > x) {
            j--;
        }
        if (i <= j) {
            std::swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
    hoarSort(mas, l, j);
    hoarSort(mas, i, r);
}

bool Sort(const std::vector<int>& mas) {
    return std::is_sorted(mas.begin(), mas.end());
}

void printArray(const std::vector<int>& mas) {
    for (const int& element : mas) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void saveToFile(const std::string& filename, const std::vector<int>& mas) {
    std::ofstream file(filename);
    for (const int& element : mas) {
        file << element << "\n";
    }
    file.close();
}

int main() {
    srand(time(0));

    const int sizes[] = { 10000, 100000, 1000000 };
    const int ranges[][2] = { {-10, 10}, {-1000, 1000}, {-100000, 100000} };
    const int totalArrays = sizeof(sizes) / sizeof(sizes[0]) * sizeof(ranges) / sizeof(ranges[0]);

    for (int size : sizes) {
        for (const auto& range : ranges) {
            std::vector<int> mas(size);
            RandMas(mas, range[0], range[1]);

            std::string filename = "array_" + std::to_string(size) + "_" + std::to_string(range[0]) + "_" + std::to_string(range[1]) + ".txt";
            saveToFile(filename, mas);

            double totalDuration = 0;
            const int iterations = 3;
            for (int i = 0; i < iterations; i++) {
                std::vector<int> tempMas = mas; 
                clock_t start = clock();
                hoarSort(tempMas, 0, size - 1);
                clock_t stop = clock();
                double duration = double(stop - start) / CLOCKS_PER_SEC;
                totalDuration += duration;

                if (!Sort(tempMas)) {
                    std::cout << "Array sort error!" << std::endl;
                    return 1;
                }
            }

            double averageDuration = totalDuration / iterations;
            std::cout << "Average running time of Hoare's algorithm for array size " << size
                << " with range [" << range[0] << ", " << range[1] << "]: "
                << averageDuration << " sec" << std::endl;
        }
    }

    return 0;
}