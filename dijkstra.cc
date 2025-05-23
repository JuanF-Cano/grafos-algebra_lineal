#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

/**
 * Class representing a graph using an adjacency matrix.
 * Supports adding nodes, edges, printing the graph,
 * and computing shortest paths using Dijkstra's algorithm.
 */
class Graph {
  private:
    unsigned int V_;  // Number of vertices
    vector<vector<int>> adjMatrix_;  // Weighted adjacency matrix

  public:
    // Default constructor
    Graph() {}

    // Constructor with initial number of vertices
    Graph(int V) {
      V_ = V;
      adjMatrix_.resize(V, vector<int>(V, 0));  // Initialize with no edges
    }

    /**
     * Adds a new node to the graph, resizing the adjacency matrix.
     * New edges are initialized to 0 (no connection).
     */
    void addNode() {
      int newSize = adjMatrix_.size() + 1;
      for (auto& row : adjMatrix_) {
        row.push_back(0);  // Add a zero column to each existing row
      }
      adjMatrix_.push_back(vector<int>(newSize, 0));  // Add a new row
      V_++;
    }

    /**
     * Adds an undirected edge between nodes u and v with a given weight.
     * If either node is out of bounds, the function exits with an error message.
     */
    void addEdge(int u, int v, int weight) {
      if (u >= adjMatrix_.size() || v >= adjMatrix_.size()) {
        cout << "Error: node out of range." << endl;
        return;
      }
      if (u == v) return;  // Avoid self-loops

      adjMatrix_[u][v] = weight;
      adjMatrix_[v][u] = weight;  // Since the graph is undirected
    }

    /**
     * Prints the weighted adjacency matrix to the console.
     * Zero-weight (nonexistent) edges are shown as dots.
     */
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

    /**
     * Dijkstra's algorithm to compute shortest paths from a source node.
     * It prints the shortest distance and path from the source to all other nodes.
     */
    void dijkstra(unsigned int source) {
      int numNodes = adjMatrix_.size();

      vector<int> distance(numNodes, numeric_limits<int>::max());  // Distance from source
      vector<bool> visited(numNodes, false);  // Track visited nodes
      vector<int> previous(numNodes, -1);  // Store predecessors to reconstruct paths

      // Min-heap priority queue storing (distance, node)
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

      distance[source] = 0;
      pq.push({0, source});  // Start from source node with distance 0

      while (!pq.empty()) {
        pair<int, int> top = pq.top();
        int dist_u = top.first;
        int u = top.second;
        pq.pop();

        if (visited[u]) continue;  // Skip already processed nodes
        visited[u] = true;

        // Explore all neighbors of node u
        for (int v = 0; v < numNodes; ++v) {
          int weight = adjMatrix_[u][v];

          // Relax the edge (u, v) if it's shorter than known distance
          if (weight != 0 && !visited[v] && dist_u + weight < distance[v]) {
            distance[v] = dist_u + weight;
            previous[v] = u;
            pq.push({distance[v], v});
          }
        }
      }

      // Output shortest paths from source
      cout << "\nShortest distances from node " << source << ":\n";
      for (int i = 0; i < numNodes; ++i) {
        if (distance[i] == numeric_limits<int>::max()) {
          cout << "Node " << i << ": unreachable\n";
        } else {
          cout << "Node " << i << ": " << distance[i] << " (path: ";
          printPath(previous, i);
          cout << ")\n";
        }
      }
    }

  private:
    /**
     * Helper function to recursively print the path from the source to the given node.
     */
    void printPath(const vector<int>& previous, int node) {
      if (previous[node] == -1) {
        cout << node;
        return;
      }
      printPath(previous, previous[node]);
      cout << " -> " << node;
    }
};

int main() {
  Graph g(6);

  // Add edges and weights
  g.addEdge(0, 1, 4);
  g.addEdge(0, 2, 4);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 3, 3);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(3, 4, 3);
  g.addEdge(5, 4, 3);

  g.printGraph();

  // Run Dijkstra's algorithm from every node
  g.dijkstra(0);
  g.dijkstra(1);
  g.dijkstra(2);
  g.dijkstra(3);
  g.dijkstra(4);
  g.dijkstra(5);

  return 0;
}