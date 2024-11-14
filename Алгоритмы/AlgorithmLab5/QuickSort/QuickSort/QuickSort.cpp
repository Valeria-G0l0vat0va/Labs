#include <iostream>
#include <ctime>
#include <chrono> 


void RandMas(int* mas, int n, int a, int b)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % (b - a + 1) + a;
    }
}

void hoarSort(int* A, int l, int r) {
    if (l >= r) {
        return;
    }
    int i = l;
    int j = r;
    int x = A[(l + r) / 2];
    while (i <= j) {
        while (A[i] < x) {
            i++;
        }
        while (A[j] > x) {
            j--;
        }
        if (i <= j) {
            std::swap(A[i], A[j]);
            i++;
            j--;
        }
    }
    hoarSort(A, l, j);
    hoarSort(A, i, r);
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

void printArray(const int* mas, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << mas[i] << " "; 
    }
    std::cout << std::endl;
}
int main() {
    srand(time(0)); 
    const int n = 1000;
    const int a = -100;
    const int b = 100;
    int mas1[n], mas2[n], mas3[n];

    RandMas(mas1, n, a, b);
    RandMas(mas2, n, a, b);
    RandMas(mas3, n, a, b);
    
    for (int k = 0; k < 3; k++) {
        int* start_mas;
        if (k == 0) {
            start_mas = mas1;
            std::cout << "Array " << k + 1 << " (original): ";
            printArray(start_mas, n);
        }
        else if (k == 1) {
            start_mas = mas2;
            std::cout << "Array " << k + 1 << " (original): ";
            printArray(start_mas, n);
        }
        else {
            start_mas = mas3;
            std::cout << "Array " << k + 1 << " (original): ";
            printArray(start_mas, n);
        }
        clock_t start = clock();
        hoarSort(start_mas, 0, n - 1);
        clock_t stop = clock();
        double duration = double(stop - start) / CLOCKS_PER_SEC;
       
        if (!Sort(start_mas, n)) {
            std::cout << "Array sort error!" << std::endl;
            return 1;
        }

        std::cout << "Array " << k + 1 << " (after sort): ";
        printArray(start_mas, n);

        std::cout << "Average running time of Hoare's algorithm for an array " << k + 1 << ": " << duration << " sec" << std::endl;
    }

    return 0;
}

