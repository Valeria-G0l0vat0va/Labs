#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include <numeric>
#include <tuple>
#include <algorithm>


void RandMas(int* mas, int n, int a, int b)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % (b - a + 1) + a;
    }
}

void Sift(int* mas, int n, int i) {
    int j = 2 * i + 1;
    int x = mas[i];
    while (j < n) {
        if (j + 1 < n && mas[j + 1] > mas[j]) {
            j++;
        }
        if (mas[j] > x) {
            mas[i] = mas[j];
            i = j;
            j = 2 * i + 1;
        }
        else {
            break;
        }
    }
    mas[i] = x;
}

void pyramidalSort(int* mas, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Sift(mas, n, i);
    for (int i = n - 1; i >= 1; i--) {
        std::swap(mas[0], mas[i]);
        Sift(mas, i, 0);
    }
}

bool Sort(int* mas, int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (mas[i] > mas[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));

    int sizes[] = { 10000, 100000, 1000000 };
    int ranges[][2] = { {-10, 10}, {-1000, 1000}, {-100000, 100000} };

    std::vector<int*> allArrays;

    for (int sizeIndex = 0; sizeIndex < 3; sizeIndex++) {
        for (int rangeIndex = 0; rangeIndex < 3; rangeIndex++) {
            int n = sizes[sizeIndex];
            int a = ranges[rangeIndex][0];
            int b = ranges[rangeIndex][1];

            int* mas = new int[n];
            RandMas(mas, n, a, b);
            allArrays.push_back(mas);

            std::ofstream file("array_" + std::to_string(sizeIndex) + "_" + std::to_string(rangeIndex) + ".txt");
            for (int i = 0; i < n; i++) {
                file << mas[i] << " ";
            }
            file.close();
        }
    }

    for (int sizeIndex = 0; sizeIndex < 3; sizeIndex++) {
        for (int rangeIndex = 0; rangeIndex < 3; rangeIndex++) {
            int n = sizes[sizeIndex];
            int a = ranges[rangeIndex][0];
            int b = ranges[rangeIndex][1];


            std::cout << "Размер массива: " << n << std::endl;
            std::cout << "Диапазон значений: [" << a << ", " << b << "]" << std::endl;

            double totalTime = 0;
            for (int l = 0; l < 3; ++l) {

                int* mas = new int[n];
                int arrayIndex = sizeIndex * 3 + rangeIndex;
                for (int k = 0; k < n; k++) {
                    mas[k] = allArrays[arrayIndex][k];
                }

                auto start = std::chrono::high_resolution_clock::now();
                pyramidalSort(mas, n);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                totalTime += duration.count();

                delete[] mas;
            }

            std::cout << "Среднее время работы пирамидальной сортировки: " << (totalTime / 3.0) << " микросекунд" << std::endl;
        }
    }
    for (int* arr : allArrays) {
        delete[] arr;
    }

    return 0;
}