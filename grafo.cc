#include <iostream>
#include <vector>

using namespace std;

class Graph {
  private:
    unsigned int V_;
    vector<vector<int>> adjMatrix_;

  public:
    // Constructor por defecto
    Graph() {}

    Graph(int V) {
      V_ = V;
      adjMatrix_.resize(V, vector<int>(V, 0));
    }

    // Agrega un nuevo nodo
    void addNode() {
        int newSize = adjMatrix_.size() + 1;

        for (auto& row : adjMatrix_) {
            row.push_back(0);
        }

        adjMatrix_.push_back(vector<int>(newSize, 0));
        
        V_++;
    }

    void addEdge(int u, int v) {
      if (u >= adjMatrix_.size() || v >= adjMatrix_.size()) {
        cout << "Error: nodo fuera de rango." << endl;
        return;
      }
      adjMatrix_[u][v] = 1;
      adjMatrix_[v][u] = 1;
    }

    void printGraph() {
        cout << "Matriz de adyacencia:\n";
        for (const auto& row : adjMatrix_) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    int numNodes() const {
        return adjMatrix_.size();
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();

    g.addNode();
    g.addEdge(5, 0);

    cout << "\nDespués de agregar el nodo 5:\n";
    g.printGraph();

    return 0;
}