#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// Union-Find (Disjoint Set Union) data structure
class UnionFind {
  private:
    vector<int> parent, rank;

  public:
    // Constructor: initializes each node to be its own parent (self-set)
    UnionFind(int n) {
      parent.resize(n);
      rank.resize(n, 0); // used for union by rank
      for (int i = 0; i < n; ++i)
        parent[i] = i;
    }

    // Find the representative (root) of the set containing x, with path compression
    int find(int x) {
      if (parent[x] != x)
        parent[x] = find(parent[x]);
      return parent[x];
    }

    // Union the sets containing x and y. Returns true if union was successful.
    bool union_sets(int x, int y) {
      int xr = find(x);
      int yr = find(y);
      if (xr == yr)
        return false; // already in the same set

      // Union by rank to keep the tree shallow
      if (rank[xr] < rank[yr])
        parent[xr] = yr;
      else if (rank[xr] > rank[yr])
        parent[yr] = xr;
      else {
        parent[yr] = xr;
        rank[xr]++;
      }

      return true;
    }
};

// Graph class for handling undirected, weighted graphs
class Graph {
  private:
    int V; // Number of vertices
    vector<tuple<int, int, int>> edges; // Edge list: (weight, node u, node v)

  public:
    // Constructor: initialize graph with V vertices
    Graph(int V) : V(V) {}

    // Add an undirected edge to the graph
    void addEdge(int u, int v, int weight) {
      edges.emplace_back(weight, u, v);
    }

    // Kruskal's algorithm to build the Minimum Spanning Tree (MST)
    void kruskal() {
      // Sort all edges in non-decreasing order of weight
      sort(edges.begin(), edges.end());

      UnionFind uf(V); // Initialize Union-Find for cycle detection
      int mst_weight = 0;

      cout << "\nMinimum Spanning Tree edges (Kruskal):\n";
      for (auto edge : edges) {
        int weight = get<0>(edge);
        int u = get<1>(edge);
        int v = get<2>(edge);

        // If including this edge doesn't cause a cycle, include it in MST
        if (uf.union_sets(u, v)) {
          cout << u << " - " << v << " (weight " << weight << ")\n";
          mst_weight += weight;
        }
      }

      cout << "Total weight of the MST: " << mst_weight << endl;
    }
};

// Main function: create a graph, add edges, and compute the MST
int main() {
  Graph g(6);
  g.addEdge(0, 1, 4);
  g.addEdge(0, 2, 4);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 3, 3);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(3, 4, 3);
  g.addEdge(5, 4, 3);

  g.kruskal();

  return 0;
}