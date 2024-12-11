#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>

void RandMas(int cost_matrix[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
            else {
                cost_matrix[i][j] = std::rand() % 100 + 1;
            }
        }
    }
}

void CompleteEnumeration(int index, int visited, int n, int start_city, int& min_cost, int& max_cost, int current_cost, int cost_matrix[100][100], int current_route[100], int& route_index, int best_route[100], bool print_route) {
    if (visited == (1 << n) - 1) {
        int total_cost = current_cost + cost_matrix[index][start_city];

        if (total_cost < min_cost) {
            min_cost = total_cost;
            for (int i = 0; i < route_index; i++) {
                best_route[i] = current_route[i];
            }
            best_route[route_index] = start_city; 
        }

        if (total_cost > max_cost) {
            max_cost = total_cost;
        }

        if (print_route) {
            std::cout << "Route: ";
            std::cout << start_city + 1 << " -> ";
            for (int i = 0; i < route_index; ++i) {
                std::cout << current_route[i] + 1;
                if (i < route_index - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << " -> " << start_city + 1 << " (cost: " << total_cost << ")" << std::endl;
        }
        return;
    }

    for (int city = 0; city < n; ++city) {
        if (!(visited & (1 << city))) {
            current_route[route_index++] = city; 

            CompleteEnumeration(city, visited | (1 << city), n, start_city, min_cost, max_cost, current_cost + cost_matrix[index][city], cost_matrix, current_route, route_index, best_route, print_route);

            route_index--; 
        }
    }
}

int Heuristic_GreedyAlgorithm(int start_city, int cost_matrix[100][100], int greedy_route[100], int& greedy_cost, int n) {
    bool visited[100] = { false };
    greedy_route[0] = start_city; 
    visited[start_city] = true; 

    int current_city = start_city;

    for (int i = 1; i < n; ++i) {
        int next_city = -1;
        int min_cost = std::numeric_limits<int>::max();

        for (int city = 0; city < n; ++city) {
            if (!visited[city] && cost_matrix[current_city][city] < min_cost) {
                min_cost = cost_matrix[current_city][city];
                next_city = city;
            }
        }

        if (next_city == -1) {
            return -1; 
        }

        greedy_route[i] = next_city;
        visited[next_city] = true;
        greedy_cost += min_cost;
        current_city = next_city;
    }

    greedy_cost += cost_matrix[current_city][start_city]; 
    greedy_route[n] = start_city; 
    return greedy_cost;
}

int main() {
    srand(time(0));

    for (int i = 0; i < 3; ++i) { 
        int n;
        int start_city;

        std::cout << "Enter the number of cities for set " << i + 1 << ": ";
        std::cin >> n;

        std::cout << "Enter the starting city(from 1 to " << n << ") : ";
        std::cin >> start_city;
        if (start_city < 1 || start_city > n) {
            std::cout << "No such city exists." << std::endl;
            return 1;
        }

        start_city--; 

        std::cout << "Set " << i + 1 << std:: endl;

        for (int j = 0; j < 3; ++j) { 
            std::cout << "Matrix: " << j + 1 << std::endl;

            int cost_matrix[100][100];
            RandMas(cost_matrix, n);

            for (int a = 0; a < n; ++a) {
                for (int b = 0; b < n; ++b) {
                    std::cout << cost_matrix[a][b] << '\t';
                }
                std::cout << std::endl;
            }

            bool print_route;
            std::cout << "Do you want to see the current route? (1 - yes, 0 - no): ";
            std::cin >> print_route;

            int min_cost = std::numeric_limits<int>::max();
            int max_cost = std::numeric_limits<int>::min();
            int current_route[100];
            int best_route[100];
            int route_index = 0;

            unsigned int start_time = clock();
            CompleteEnumeration(start_city, 1 << start_city, n, start_city, min_cost, max_cost, 0, cost_matrix, current_route, route_index, best_route, print_route);
            unsigned int end_time = clock();
            unsigned int elapsed_time = end_time - start_time;

            std::cout << "Minimum cost of complete enumeration:" << min_cost << std::endl;
            std::cout << "Maximum cost of complete enumeration: " << max_cost << std:: endl;
            std::cout << "Complete enumeration execution time: " << elapsed_time << " sec" << std::endl;

            int greedy_route[100 + 1]; 
            int greedy_cost = 0;

            start_time = clock();
            Heuristic_GreedyAlgorithm(start_city, cost_matrix, greedy_route, greedy_cost, n);
            end_time = clock();
            elapsed_time = end_time - start_time;

            std::cout << " (greedy algorithm cost: " << greedy_cost << ")" << std::endl;
            std::cout << "Greedy algorithm execution time: " << elapsed_time << " sec" << std::endl;
            float percent = std::abs(100 - ((100 * greedy_cost - 100 * min_cost) / (max_cost - min_cost)));
            std::cout << "Solution quality: " << percent << "%" << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}
