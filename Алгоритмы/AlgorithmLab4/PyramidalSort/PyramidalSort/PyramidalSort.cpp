#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <chrono> 

void RandMas(int* mas, int n, int a, int b)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % (b - a + 1) + a;
    }
}

void Shift2(int* mas, int n, int i) {
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
        Shift2(mas, n, i);
    for (int i = n - 1; i >= 1; i--) {
        std::swap(mas[0], mas[i]);
        Shift2(mas, i, 0);
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

    int n = 10; 
    int a = -10; 
    int b = 10;

    int* mas = new int[n];  
    RandMas(mas, n, a, b); 

    std::cout << "Array before sorting: ";
    for (int i = 0; i < n; i++) {
        std::cout << mas[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Step 1: building pyramid " << std::endl;
    for (int i = n / 2 - 1; i >= 0; i--) {
        Shift2(mas, n, i);
        std::cout << "Array after element sifting " << i << ": ";
        for (int j = 0; j < n; j++) {
            std::cout << mas[j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Step 2: Sorting the pyramid" << std::endl;
    for (int i = n - 1; i >= 1; i--) {
        std::swap(mas[0], mas[i]);
        std::cout << "Array after exchange of elements " << 0 << " and " << i << ": ";
        for (int j = 0; j < n; j++) {
            std::cout << mas[j] << " ";
        }
        std::cout << std::endl;

        Shift2(mas, i, 0); 
        std::cout << "Array after element sifting " << 0 << ": ";
        for (int j = 0; j < n; j++) {
            std::cout << mas[j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << mas[i] << " ";
    }
    std::cout << std::endl;

    delete[] mas; 
    return 0;
}

