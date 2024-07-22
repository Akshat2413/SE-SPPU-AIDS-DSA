#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

const int INF = numeric_limits<int>::max(); // Define a constant for infinity

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix to store edge weights

public:
    Graph(int vertices) : V(vertices), adjMatrix(vertices, vector<int>(vertices, INF)) {} // Constructor to initialize the graph with V vertices and all edges set to INF

    // Function to add an edge between vertices u and v with weight 'weight'
    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = adjMatrix[v][u] = weight;
    }

    // Function to display the adjacency matrix
    void display() {
        cout << "Adjacency matrix:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (adjMatrix[i][j] == INF)
                    cout << "INF "; // Print INF if no edge exists
                else
                    cout << adjMatrix[i][j] << "   "; // Print edge weight
            }
            cout << endl;
        }
    }

    // Function to find the minimum spanning tree using Prim's algorithm
    int primMST() {
        vector<bool> visited(V, false); // Array to keep track of visited vertices
        int totalWeight = 0; // Variable to store total weight of MST

        // Priority queue to store pairs of {weight, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0}); // Push the first vertex (0) with weight 0

        while (!pq.empty()) {
            int u = pq.top().second; // Get the vertex with minimum weight
            int weight = pq.top().first; // Get the weight
            pq.pop();

            if (visited[u])
                continue; // Skip if already visited

            visited[u] = true; // Mark vertex as visited
            totalWeight += weight; // Add weight to total weight

            // Iterate through all adjacent vertices of u
            for (int v = 0; v < V; ++v) {
                // If there's an edge from u to v and v is not visited
                if (adjMatrix[u][v] != INF && !visited[v]) {
                    // Add v to priority queue with weight of the edge u-v
                    pq.push({adjMatrix[u][v], v});
                }
            }
        }
        return totalWeight; // Return total weight of MST
    }
};

int main() {
    int ch, v, e;
    cout << "Enter the number of branches: ";
    cin >> v;

    Graph g(v); // Create a graph with v vertices

    cout << "\nEnter the number of connections: ";
    cin >> e;

    // Input connections and their weights
    for (int i = 0; i < e; i++) {
        int l, u, w;
        cout << "Enter the end branches of connections: ";
        cin >> l >> u;
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;
        g.addEdge(l - 1, u - 1, w); // Add edge to the graph
    }

    do {
        cout << "==========PRIM'S ALGORITHM=================\n";
        cout << "\n1. Display\n";
        cout << "2. Minimum\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "*******DISPLAY THE CONTENTS********\n";
                g.display(); // Display adjacency matrix
                break;

            case 2:
                cout << "*********MINIMUM************\n";
                cout << "The minimum total cost of connections of all branches is: " << g.primMST() << endl;
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
                break;
        }

    } while (ch != 3);

    return 0;
}

