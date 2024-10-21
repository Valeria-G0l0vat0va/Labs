#include<stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include<Windows.h>

using namespace std;

void RandMas(int* mas, int n, int a, int b)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % (b - a + 1) + a;
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

void shellSort(int* a, int n, int* h, int t) {
    for (int i = t - 1; i >= 0; i--) { 
        int s = h[i];
        for (int j = s; j < n; j++) { 
            int temp = a[j];
            int k = j;
            while (k >= s && a[k - s] > temp) {
                a[k] = a[k - s];
                k -= s;
            }
            a[k] = temp;
        }
    }
}

void shellIncrements(int* h, int n, int& t) {
    t = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        h[t++] = gap;
    }
}

void powerOfTwoMinusOneIncrements(int* h, int n, int& t) {
    t = 0;
    int m = 1;
    while (pow(2, m) - 1 <= n) {
        h[t++] = pow(2, m) - 1; m++;
    }
}
void knuthIncrements(int* h, int n, int& t) {
    t = 0;
    h[t++] = 1;
    int k = 1;
    while (3 * k + 1 <= n) {
        h[t++] = 3 * k + 1;
        k *= 3;
    }
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    int sizes[] = { 10000, 100000, 1000000 };
    int ranges[][2] = { {-10,10}, {-1000,1000}, {-100000,100000} };
    int incrementAlgorithms[] = { 0, 1, 2 };
    for (int sizeIndex = 0; sizeIndex < 3; sizeIndex++)
    {
        for (int rangeIndex = 0; rangeIndex < 3; rangeIndex++)
        {
            for (int algorithmIndex = 0; algorithmIndex < 3; algorithmIndex++)
            {
                int n = sizes[sizeIndex];
                int a = ranges[rangeIndex][0];
                int b = ranges[rangeIndex][1];
                int incrementAlgorithm = incrementAlgorithms[algorithmIndex];
                int maxIncrements = n / 2;
                int* h = new int[maxIncrements];

                int t;
                if (incrementAlgorithm == 0) {
                    shellIncrements(h, n, t);
                }
                else if (incrementAlgorithm == 1) {
                    powerOfTwoMinusOneIncrements(h, n, t);
                }
                else
                    knuthIncrements(h, n, t);

                int* mas = new int[n];
                RandMas(mas, n, a, b);

                cout << "Размер массива: " << n << endl;
                cout << "Диапазон значений: [" << a << ", " << b << "]" << endl;
                cout << "Алгоритм выбора промежутков: ";
                switch (incrementAlgorithm) {
                case 0:
                    cout << "Shell's Original" << endl;
                    break;
                case 1:
                    cout << "2^m– 1" << endl;
                    break;
                case 2:
                    cout << "Knuth" << endl;
                    break;
                }

                double totalTime = 0;
                for (int l = 0; l < 3; l++) {
                    clock_t start = clock();
                    shellSort(mas, n, h, t);  
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC; 
                    totalTime += duration;

                    if (!Sort(mas, n)) {
                        cout << "Ошибка: массив не отсортирован" << endl;
                    }
                    RandMas(mas, n, a, b);
                }
                cout << "Среднее время работы: " << (totalTime / 3.0) * 1000000 << " микросекунд" << endl;

                delete[] h;
                delete[] mas;
            }
        }
    }
    return 0;
}