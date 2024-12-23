#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

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

    int size1 = 10000;
    int size2 = 100000;
    int size3 = 1000000;
    int* arr1 = new int[size1];
    int* arr2 = new int[size2];
    int* arr3 = new int[size3];

    RandMas(arr1, size1, -10, 10);
    RandMas(arr2, size2, -1000, 1000);
    RandMas(arr3, size3, -100000, 100000);

    std::ofstream file1("array1.txt");
    std::ofstream file2("array2.txt");
    std::ofstream file3("array3.txt");

    for (int i = 0; i < size1; i++) {
        file1 << arr1[i] << " ";
    }
    for (int i = 0; i < size2; i++) {
        file2 << arr2[i] << " ";
    }
    for (int i = 0; i < size3; i++) {
        file3 << arr3[i] << " ";
    }

    file1.close();
    file2.close();
    file3.close();

    pyramidalSort(arr1, size1);
    pyramidalSort(arr2, size2);
    pyramidalSort(arr3, size3);

    auto start1 = std::chrono::high_resolution_clock::now();
    pyramidalSort(arr1, size1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    pyramidalSort(arr2, size2);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

    auto start3 = std::chrono::high_resolution_clock::now();
    pyramidalSort(arr3, size3);
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);

    std::ofstream file1_sorted("array1_sorted.txt");
    std::ofstream file2_sorted("array2_sorted.txt");
    std::ofstream file3_sorted("array3_sorted.txt");

    for (int i = 0; i < size1; i++) {
        file1_sorted << arr1[i] << " ";
    }
    for (int i = 0; i < size2; i++) {
        file2_sorted << arr2[i] << " ";
    }
    for (int i = 0; i < size3; i++) {
        file3_sorted << arr3[i] << " ";
    }

    file1_sorted.close();
    file2_sorted.close();
    file3_sorted.close();

    std::cout << "Sorted array 1: ";
    for (int i = 0; i < size1; i++) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Sorted array 2: ";
    for (int i = 0; i < size2; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Sorted array 3: ";
    for (int i = 0; i < size3; i++) {
        std::cout << arr3[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Time taken to sort array 1: " << duration1.count() << " microseconds" << std::endl;
    std::cout << "Time taken to sort array 2: " << duration2.count() << " microseconds" << std::endl;
    std::cout << "Time taken to sort array 3: " << duration3.count() << " microseconds" << std::endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}

