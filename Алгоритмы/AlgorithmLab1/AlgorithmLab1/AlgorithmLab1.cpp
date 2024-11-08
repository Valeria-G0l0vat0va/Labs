#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include<Windows.h>

using namespace std;
using namespace chrono;

int minCost = INT_MAX;
int bestPath[10];
int currentPath[10];
bool visited[10];

void generate_matrix(int matrix[][10], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; 
            }
            else {
                matrix[i][j] = rand() % 100 + 1; 
            }
        }
    }
}

void print_matrix(int matrix[][10], int size) {
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void findHamiltonianCycle(int pos, int cost, int count, int matrix[][10], int size) {
    if (count == size && matrix[pos][0]) {
        if (cost + matrix[pos][0] < minCost) {
            minCost = cost + matrix[pos][0];
            for (int i = 0; i < size; i++) {
                bestPath[i] = currentPath[i];
            }
            bestPath[size] = 0; 
        }
        return;
    }
    for (int i = 0; i < size; i++) {
        if (!visited[i] && matrix[pos][i]) {
            visited[i] = true; 
            currentPath[count] = i; 
            findHamiltonianCycle(i, cost + matrix[pos][i], count + 1, matrix, size); 
            visited[i] = false; 
        }
    }
}

int algorithmGreedy(int matrix[][10], int n) {
    bool visited[10] = { false }; 
    int totalCost = 0;
    int curr = 0; 
    for (int i = 0; i < n; ++i) {
        visited[curr] = true; 
        int next = -1;
        int minCost = INT_MAX;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && matrix[curr][j] < minCost) {
                minCost = matrix[curr][j];
                next = j;
            }
        }
        if (next != -1) { 
            totalCost += minCost;
            curr = next;
        }
    }
    totalCost += matrix[curr][0]; 
    return totalCost;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int sizes[] = { 4,6,8,10 };
    const int numRuns = 3;
    clock_t start, stop;

    for (int s : sizes) {
        cout << "Размер матрицы: " << s << "x" << s << endl;
        for (int run = 1; run <= numRuns; run++) {
            int matrix[10][10];
            generate_matrix(matrix, s); 
            print_matrix(matrix, s);

            for (int i = 0; i < 10; i++) {
                visited[i] = false;
            }
            visited[0] = true;
            minCost = INT_MAX;

            start = clock();
            currentPath[0] = 0;
            findHamiltonianCycle(0, 0, 1, matrix, s);
            stop = clock();
            double duration1 = double(stop - start) / CLOCKS_PER_SEC;

            start = clock();
            int heuristicCost = algorithmGreedy(matrix, s);
            stop = clock();
            double duration2 = double(stop - start) / CLOCKS_PER_SEC;
            int percentQuality = 0;
            if (minCost != INT_MAX) {
                if (heuristicCost == 0) {
                    percentQuality = 100;
                }
                else {
                    percentQuality = ((heuristicCost - minCost) * 100) / heuristicCost;
                }
            }

            cout << "Launch " << run << ":" << endl;
            cout << "Best result1: " << minCost << endl;
            cout << "Время работы точного алгоритма: " << duration1 << " sec" << endl;
            cout << "Result (heuristic algorithm): " << heuristicCost << endl;
            cout << "Heuristic algorithm running time: " << duration2 << " sec" << endl;
            cout << "Solution quality of heuristic algorithm: " << percentQuality << "%" << endl << endl;
        }
        cout << endl;
    }
    return 0;
}