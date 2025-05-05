#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define NUM_NODES 6

// Landmarks
string landmarks[NUM_NODES] = {
    "College Gate", "Library", "Cafeteria", 
    "Auditorium", "Admin Block", "Playground"
};

// ---------------- DFS using Adjacency Matrix ----------------
class DFSGraph {
private:
    int adjMatrix[NUM_NODES][NUM_NODES];
    bool visited[NUM_NODES];

public:
    DFSGraph() {
        for (int i = 0; i < NUM_NODES; i++) {
            visited[i] = false;
            for (int j = 0; j < NUM_NODES; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void DFS(int node) {
        visited[node] = true;
        cout << landmarks[node] << " -> ";

        for (int i = 0; i < NUM_NODES; i++) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                DFS(i);
            }
        }
    }
};

// ---------------- BFS using Adjacency List ----------------
class BFSGraph {
private:
    vector<int> adjList[NUM_NODES];

public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void BFS(int start) {
        vector<bool> visited(NUM_NODES, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << landmarks[node] << " -> ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

// ---------------- Main ----------------
int main() {
    // Creating and populating DFS graph
    DFSGraph dfsGraph;
    dfsGraph.addEdge(0, 1); // College Gate - Library
    dfsGraph.addEdge(0, 2); // College Gate - Cafeteria
    dfsGraph.addEdge(1, 3); // Library - Auditorium
    dfsGraph.addEdge(2, 4); // Cafeteria - Admin Block
    dfsGraph.addEdge(3, 5); // Auditorium - Playground
    dfsGraph.addEdge(4, 5); // Admin Block - Playground

    cout << "DFS Traversal (Adjacency Matrix):\n";
    dfsGraph.DFS(0);
    cout << "END\n\n";

    // Creating and populating BFS graph
    BFSGraph bfsGraph;
    bfsGraph.addEdge(0, 1);
    bfsGraph.addEdge(0, 2);
    bfsGraph.addEdge(1, 3);
    bfsGraph.addEdge(2, 4);
    bfsGraph.addEdge(3, 5);
    bfsGraph.addEdge(4, 5);

    cout << "BFS Traversal (Adjacency List):\n";
    bfsGraph.BFS(0);
    cout << "END\n";

    return 0;
}
