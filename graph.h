#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <limits>

class Graph {
public:
    int numVertices; // Number of vertices
    int numEdges;    // Number of edges
    bool directed;   // Indicates if the graph is directed
    int flg;         // Flag for edge insertion mode
    int beginning;   // Source vertex for single-source operations
    int endpoint;    // Destination vertex for single-pair operations

    std::vector<pVERTEX> V; // Vector of vertex pointers
    std::vector<pNODE> ADJ; // Adjacency list as a vector of NODE pointers

    Graph(int vertices, int edges, bool isDirected, int insertionflg);
    ~Graph();

    void addEdge(int index, int u, int v, double w, bool atRear);
    void readGraph(const std::string& filename);
    void printAdj() const;

    void singleSource(int src);
    void singlePair(int src, int dest);
    void printLength(int s, int t) const;
    void printPath(int s, int t) const;
};

#endif
