#include <iostream>
#include <vector>
#include "matrix_utils.h"

using namespace std;

class Graph {
  private:
    unsigned int V_;
    vector<vector<int>> adjMatrix_;

    // Performs logical OR between two matrices
    vector<vector<int>> matrixOr(const vector<vector<int>>& A, const vector<vector<int>>& B) {
      int n = A.size();
      vector<vector<int>> result(n, vector<int>(n, 0));
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          result[i][j] = A[i][j] || B[i][j];
      return result;
    }

    // Generates an identity matrix of size n x n
    vector<vector<int>> identityMatrix(int n) {
      vector<vector<int>> id(n, vector<int>(n, 0));
      for (int i = 0; i < n; ++i)
        id[i][i] = 1;
      return id;
    }

  public:
    // Default constructor
    Graph() {}

    // Constructor with number of vertices
    Graph(int V) {
      V_ = V;
      adjMatrix_.resize(V, vector<int>(V, 0));
    }

    // Adds a new node to the graph, resizing the adjacency matrix
    void addNode() {
      int newSize = adjMatrix_.size() + 1;

      for (auto& row : adjMatrix_) {
        row.push_back(0);
      }

      adjMatrix_.push_back(vector<int>(newSize, 0));
      V_++;
    }

    // Adds a directed edge from u to v
    void addEdge(int u, int v) {
      if (u >= adjMatrix_.size() || v >= adjMatrix_.size()) {
        cout << "Error: node out of range." << endl;
        return;
      }
      adjMatrix_[u][v] = 1;
    }

    // Prints the adjacency matrix representing the graph
    void printGraph() {
      cout << "Adjacency Matrix:\n";
      for (const auto& row : adjMatrix_) {
        for (int val : row) {
          cout << val << " ";
        }
        cout << endl;
      }
    }

    // Returns the number of nodes in the graph
    int numNodes() const {
      return adjMatrix_.size();
    }

    // Computes the matrix C = I OR A OR A^2 OR ... OR A^n,
    // which represents reachability for strongly connected components calculation
    vector<vector<int>> stronglyConnectedComponents() {
      int n = adjMatrix_.size();
      vector<vector<int>> C = identityMatrix(n);
      vector<vector<int>> powerA = adjMatrix_;

      for (int i = 0; i < n; ++i) {
        C = matrixOr(C, powerA);
        powerA = matrixMultiply(powerA, adjMatrix_);
      }

      return C;
    }

    // Prints the matrix C used for strongly connected components
    void printC() {
      vector<vector<int>> C = stronglyConnectedComponents();
      cout << "\nMatrix C = I OR A OR A^2 OR ... OR A^n:\n";
      for (const auto& row : C) {
        for (int val : row) {
          cout << val << " ";
        }
        cout << "\n";
      }
    }
    
    // Prints the matrix CSS (strongly connected components)
    void printSCC() {
      vector<vector<int>> scc = stronglyConnectedComponents();
      cout << "\nMatriz de Componentes Fuertemente Conexos:\n";
      for (const auto& row : scc) {
          for (int val : row) {
              cout << val << " ";
          }
          cout << "\n";
      }
    }
};

int main() {
  Graph g(6);

  g.addEdge(0, 1);
  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
  g.addEdge(5, 0);

  g.printC();
  g.printSCC();

  return 0;
}