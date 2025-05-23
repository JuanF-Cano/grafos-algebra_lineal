#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

class Graph {
  private:
    unsigned int V_;
    vector<vector<int>> adjMatrix_;

  public:
    // Default constructor
    Graph() {}

    // Constructor with number of nodes
    Graph(int V) {
      V_ = V;
      adjMatrix_.resize(V, vector<int>(V, 0));  // Initialize matrix with zeros (no edges)
    }

    // Add a new node to the graph, resizing the matrix
    void addNode() {
      int newSize = adjMatrix_.size() + 1;

      for (auto& row : adjMatrix_) {
        row.push_back(0);  // Add zero column to existing rows
      }

      adjMatrix_.push_back(vector<int>(newSize, 0));  // Add new row with zeros

      V_++;
    }

    // Add an undirected edge with a weight
    void addEdge(int u, int v, int weight) {
      if (u >= adjMatrix_.size() || v >= adjMatrix_.size()) {
        cout << "Error: node out of range." << endl;
        return;
      }
      if (u == v) return;  // Avoid loops

      adjMatrix_[u][v] = weight;
      adjMatrix_[v][u] = weight;
    }

    // Print adjacency matrix
    void printGraph() {
      cout << "Weighted adjacency matrix:\n";
      for (const auto& row : adjMatrix_) {
        for (int val : row) {
          if (val == 0)
            cout << ". ";
          else
            cout << val << " ";
        }
        cout << endl;
      }
    }

    // Return number of nodes
    int numNodes() const {
      return adjMatrix_.size();
    }

    // Prim's algorithm to find Minimum Spanning Tree using priority queue
    void prims(unsigned int initialNode) {
      int numNodes = adjMatrix_.size();

      vector<int> mstParent(numNodes, -1); // Store parent of each node in MST
      vector<int> minWeight(numNodes, numeric_limits<int>::max()); // Min edge weight to MST
      vector<bool> included(numNodes, false); // Track included nodes

      // Min-heap priority queue: pairs of (weight, node)
      priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

      minWeight[initialNode] = 0;
      pq.push({0, initialNode});  // Start from node 0 with weight 0

      while (!pq.empty()) {
        pair<int, int> top = pq.top();
        int weight = top.first;
        int u = top.second;
        pq.pop();

        if (included[u]) continue;  // Skip if already included

        included[u] = true;

        // Update neighbors of u
        for (int v = 0; v < numNodes; v++) {
          int edgeWeight = adjMatrix_[u][v];
          if (edgeWeight != 0 && !included[v] && edgeWeight < minWeight[v]) {
            minWeight[v] = edgeWeight;
            mstParent[v] = u;
            pq.push({edgeWeight, v});
          }
        }
      }

      cout << "\nEdges in the Minimum Spanning Tree Starting in Node " << initialNode << ":\n";
      int totalWeight = 0;
      for (int node = 1; node < numNodes; ++node) {
        if (mstParent[node] != -1) {
          cout << mstParent[node] << " - " << node << " (weight " << adjMatrix_[node][mstParent[node]] << ")\n";
          totalWeight += adjMatrix_[node][mstParent[node]];
        }
      }
      cout << "Total weight of MST: " << totalWeight << endl;
    }
};

int main() {
  int numNodes = 6;
  Graph g(numNodes);

  // Add weighted edges
  g.addEdge(0, 1, 4);
  g.addEdge(0, 2, 4);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 3, 3);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(3, 4, 3);
  g.addEdge(5, 4, 3);

  g.printGraph();

  g.prims(0);
  g.prims(1);
  g.prims(2);
  g.prims(3);
  g.prims(4);
  g.prims(5);

  return 0;
}
