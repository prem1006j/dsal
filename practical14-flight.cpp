#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define NUM_CITIES 5

string cityNames[NUM_CITIES] = {
    "Delhi", "Mumbai", "Kolkata", "Chennai", "Bangalore"
};

// Each edge is a pair: (destination, cost)
vector<pair<int, double>> adjList[NUM_CITIES];

// Add a directed or undirected flight
void addFlight(int from, int to, double time) {
    adjList[from].push_back({to, time});
    adjList[to].push_back({from, time}); // Assuming undirected (bidirectional) flights
}

// Check if graph is connected using BFS
bool isConnected() {
    vector<bool> visited(NUM_CITIES, false);
    queue<int> q;

    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        int city = q.front();
        q.pop();

        for (auto neighbor : adjList[city]) {
            int dest = neighbor.first;
            if (!visited[dest]) {
                visited[dest] = true;
                q.push(dest);
            }
        }
    }

    // Check if all cities are visited
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

void printGraph() {
    cout << "Flight Map (Adjacency List):\n";
    for (int i = 0; i < NUM_CITIES; i++) {
        cout << cityNames[i] << " -> ";
        for (auto edge : adjList[i]) {
            cout << "(" << cityNames[edge.first] << ", " << edge.second << "hrs) ";
        }
        cout << "\n";
    }
}

int main() {
    // Adding flights
    addFlight(0, 1, 2);    // Delhi - Mumbai
    addFlight(0, 2, 1.5);  // Delhi - Kolkata
    addFlight(1, 3, 2.5);  // Mumbai - Chennai
    addFlight(2, 3, 2);    // Kolkata - Chennai
    addFlight(3, 4, 1);    // Chennai - Bangalore

    printGraph();

    // Check connectivity
    if (isConnected()) {
        cout << "\nThe flight network is CONNECTED.\n";
    } else {
        cout << "\nThe flight network is NOT CONNECTED.\n";
    }

    return 0;
}
