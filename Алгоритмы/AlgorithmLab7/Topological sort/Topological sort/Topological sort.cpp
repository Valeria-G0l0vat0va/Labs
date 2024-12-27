#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    int V; 
    vector<vector<int>> matrix; 

    Graph(int V);
    void addEdge(int v, int w);
    void topologicalSort();
    void topologicalSortUtil(int v, vector<bool>& visited, vector<int>& result);
};

Graph::Graph(int V) {
    this->V = V;
    matrix.resize(V);
}

void Graph::addEdge(int v, int w) {
    matrix[v].push_back(w); 
}

void Graph::topologicalSortUtil(int v, vector<bool>& visited, vector<int>& result) {
    visited[v] = true; 
    for (int i : matrix[v]) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, result);
        }
    }
    result.push_back(v); 
}

void Graph::topologicalSort() {
    vector<bool> visited(V, false);
    vector<int> result; 
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, result);
        }
    }

    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
}

int main() {
    Graph g(6); 
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Topological Sort Graph: ";
    g.topologicalSort();

    return 0;
}
