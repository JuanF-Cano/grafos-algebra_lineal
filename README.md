/*
# Graphs and Linear Algebra

Repository implementing matrix operations applied to directed graphs using linear algebra. Contains functions to handle adjacency matrices and compute strongly connected components via matrix powers and logical matrix operations.

---

## Contents

- **matrix_utils.h**: Library with functions for dot product, transpose, and matrix multiplication.  
- **graph.cpp**: Implementation of the `Graph` class that uses adjacency matrices to represent directed graphs and compute the strongly connected components matrix.  
- **main.cpp**: Example program that creates a graph, adds nodes/edges, and displays results.

---

## Description

This project explores how to use linear algebra to analyze properties of directed graphs, specifically identifying strongly connected components (SCC). It is based on representing the graph by adjacency matrices and computing the matrix:

C = I OR A OR A<sup>2</sup> OR A<sup>3</sup> OR ... OR A<sup>n</sup>

where:

- I is the identity matrix.  
- A is the adjacency matrix.  
- OR is the element-wise logical OR operation.  
- A^k is the k-th power of matrix A.  

The resulting matrix C is used to determine strong connectivity in the graph.

---

## Usage

1. Clone the repository:
```
git clone https://github.com/JuanF-Cano/grafos-algebra_lineal.git
cd grafos-algebra_lineal
```
2. Compile the files (example with g++):
```
g++ -o graph_exec main.cpp graph.cpp
```
3. Run the program:
```
./graph_exec
```
---

## Main functions

- dotProduct: Dot product between vectors.  
- transpose: Transpose of a matrix.  
- matrixMultiply: Multiplication of square matrices.  
- Graph:  
  - addNode: Adds a node to the graph.  
  - addEdge: Adds a directed edge.  
  - printGraph: Prints the adjacency matrix.  
  - stronglyConnectedComponents: Computes the SCC matrix C.  
  - printC: Displays matrix C.  

---

## Requirements

- Modern C++ compiler (C++11 or newer).  
- Operating system compatible with standard compilers (Linux, macOS, Windows with MinGW).  

---

## Author

Juan F. Cano  
https://github.com/JuanF-Cano  

---

## License

This project is under the MIT license. See LICENSE file for details.
*/
