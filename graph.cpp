#include "graph.h"
#include <iostream>
#include <stack>
#include <limits>
#include <fstream>
#include <iomanip>
#include "heap.h" 

Graph::Graph(int vertices, int edges, bool isDirected, int insertionflg)
    : numVertices(vertices), numEdges(edges), directed(isDirected), flg(insertionflg) {
    if (numVertices <= 0 || numEdges < 0) {
        std::cerr << "Invalid graph dimensions\n";
        exit(1);
    }

    V.resize(numVertices + 1);
    ADJ.resize(numVertices + 1, nullptr);

    for (int i = 1; i <= numVertices; ++i) {
        V[i] = new VERTEX{i, WHITE, DBL_MAX, -1, -1};
    }
}

Graph::~Graph() {
    for (int i = 1; i <= numVertices; ++i) {
        delete V[i];
        while (ADJ[i] != nullptr) {
            pNODE temp = ADJ[i];
            ADJ[i] = ADJ[i]->next;
            delete temp;
        }
    }
}

void Graph::addEdge(int index, int u, int v, double w, bool atRear) {
    if (u < 1 || u > numVertices || v < 1 || v > numVertices) {
        std::cerr << "Invalid vertex index in addEdge\n";
        return;
    }

    pNODE newNode = new NODE{index, u, v, w, nullptr};
    if (atRear) {
        if (!ADJ[u]) {
            ADJ[u] = newNode;
        } else {
            pNODE temp = ADJ[u];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    } else {
        newNode->next = ADJ[u];
        ADJ[u] = newNode;
    }

    if (!directed) {
        pNODE reverseNode = new NODE{index, v, u, w, nullptr};
        if (atRear) {
            if (!ADJ[v]) {
                ADJ[v] = reverseNode;
            } else {
                pNODE temp = ADJ[v];
                while (temp->next) temp = temp->next;
                temp->next = reverseNode;
            }
        } else {
            reverseNode->next = ADJ[v];
            ADJ[v] = reverseNode;
        }
    }
}

void Graph::readGraph(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }

    int n, m;
    infile >> n >> m;

    int index, u, v;
    double w;
    for (int i = 0; i < m; ++i) {
        infile >> index >> u >> v >> w;
        addEdge(index, u, v, w, flg);
    }

    infile.close();
}

void Graph::printAdj() const {
    for (int i = 1; i <= numVertices; ++i) {
        std::cout << "ADJ[" << i << "]:";
        pNODE temp = ADJ[i];
        while (temp) {
            std::cout << "-->[" << temp->u << " " << temp->v << ": " 
                      << std::fixed << std::setprecision(2) << temp->w << "]";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}

void Graph::singleSource(int src) {
    if (src < 1 || src > numVertices) {
        std::cerr << "Invalid source vertex\n";
        return;
    }

    beginning = src;
    endpoint = -1;

    for (int i = 1; i <= numVertices; ++i) {
        V[i]->key = DBL_MAX;
        V[i]->pi = -1;
    }
    V[src]->key = 0;

    MinHeap heap(numVertices);
    for (int i = 1; i <= numVertices; ++i) {
        heap.insert(V[i]);
    }

    while (!heap.isEmpty()) {
        pVERTEX u = heap.extractMinimum();
        pNODE adj = ADJ[u->index];
        while (adj) {
            pVERTEX v = V[adj->v];
            double newDist = u->key + adj->w;
            if (v->key > newDist) {
                v->key = newDist;
                heap.decreaseKey(v->index, newDist);
                v->pi = u->index;
            }
            adj = adj->next;
        }
    }
}

void Graph::singlePair(int src, int dest) {
    singleSource(src);
    endpoint = dest;
}

void Graph::printLength(int s, int t) const {
    if (s == beginning && (t == endpoint || endpoint == -1)) {
        if (V[t]->key != DBL_MAX) {
            std::cout << "The length of the shortest path from " << s << " to " << t << " is:     " 
                      << std::fixed << std::setprecision(2) << V[t]->key << "\n";
        } else {
            std::cout << "There is no path from " << s << " to " << t << ".\n";
        }
    } else {
        std::cerr << "Invalid PrintLength instruction\n";
    }
}

void Graph::printPath(int s, int t) const {
    if (s == beginning && (t == endpoint || endpoint == -1)) {
        if (V[t]->key != DBL_MAX) {
            std::stack<int> path;
            for (int v = t; v != -1; v = V[v]->pi) {
                path.push(v);
            }
            std::cout << "The shortest path from " << s << " to " << t << " is:\n";
            while (!path.empty()) {
                int current = path.top();
                path.pop();
                std::cout << "[" << current << ":  " 
                          << std::fixed << std::setprecision(2) 
                          << std::setw(6) << V[current]->key << "]";
                if (!path.empty()) {
                    std::cout << "-->";
                }
            }
            std::cout << ".\n";
        } else {
            std::cout << "There is no path from " << s << " to " << t << ".\n";
        }
    } else {
        std::cerr << "Invalid PrintPath instruction\n";
    }
}




