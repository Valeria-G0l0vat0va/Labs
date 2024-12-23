#include "../../../../OOP/BoolMatrix/BoolMatrix/BoolMatrix/BoolMatrix.h" 
#include <iostream> 
#include <vector>
#include <queue>

void TopologicalSort(BoolMatrix& bm) {
    std::vector<int> result;
    std::vector<bool> visited(bm.getCols(), false);
    std::vector<int> inDegree(bm.getCols(), 0); 

    for (int col = 0; col < bm.getCols(); ++col) {
        for (int row = 0; row < bm.getRows(); ++row) {
            if (bm.get(row, col)) {
                inDegree[col]++;
            }
        }
    }

    std::queue<int> queue;
    for (int col = 0; col < bm.getCols(); ++col) {
        if (inDegree[col] == 0) {
            queue.push(col);
        }
    }

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop(); 
        result.push_back(current);

        for (int i = 0; i < bm.getRows(); ++i) {
            if (bm.get(current, i)) {
                bm.invertComponent(current, i); 
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    queue.push(i);
                }
            }
        }
    }

    if (result.size() != bm.getCols()) {
        std::cout << "The graph contains a cycle. Topological sorting is impossible." << std::endl;
        return;
    }

    std::cout << "Topological order: ";
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
int main() {
    const int vertices = 6;
    BoolMatrix bm(vertices, vertices, false);

    bm.invertComponent(5, 2);  
    bm.invertComponent(5, 0); 
    bm.invertComponent(4, 0); 
    bm.invertComponent(4, 1);
    bm.invertComponent(2, 3); 
    bm.invertComponent(0, 1); 
    bm.invertComponent(3, 1); 

    TopologicalSort(bm);

    return 0;
}
