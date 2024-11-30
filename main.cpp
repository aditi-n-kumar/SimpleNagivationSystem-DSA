#include "main.h"
#include "util.h"
#include "stack.h"
#include "heap.h"
#include "graph.h"
#include <iostream>
#include <string>

void handleCommands(Graph& graph) {
    std::string cmmd;
    while (std::cin >> cmmd) {
        if (cmmd == "Stop") {
            break;
        } else if (cmmd == "PrintADJ") {
            graph.printAdj();
        } else if (cmmd == "SingleSource") {
            int source;
            std::cin >> source;
            graph.singleSource(source);
        } else if (cmmd == "SinglePair") {
            int source, endpoint;
            std::cin >> source >> endpoint;
            graph.singlePair(source, endpoint);
        } else if (cmmd == "PrintLength") {
            int s, t;
            std::cin >> s >> t;
            graph.printLength(s, t);
        } else if (cmmd == "PrintPath") {
            int s, t;
            std::cin >> s >> t;
            graph.printPath(s, t);
        } else {
            std::cerr << "Invalid instruction.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <directed> <flag>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    //bool isDirected = std::stoi(argv[2]);
    std::string graphType = argv[2];
    //int flag = std::stoi(argv[3]);
    int flag;

    try {
        flag = std::stoi(argv[3]);
        if (flag < 0 || flag > 1) {
            throw std::invalid_argument("Invalid range");
        }
    } catch (...) {
        std::cerr << "Error: <flag> must be 0 or 1.\n";
        return 1;
    }

    bool isDirected;
    if (graphType == "DirectedGraph") {
        isDirected = true;
    } else if (graphType == "UndirectedGraph") {
        isDirected = false;
    } else {
        std::cerr << "Error: <graph_type> must be DirectedGraph or UndirectedGraph.\n";
        return 1;
    }
    
    std::ifstream infile(inputFile);
    if (!infile) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    int n, m;
    infile >> n >> m;

    Graph graph(n, m, isDirected, flag);
    graph.readGraph(inputFile);

    handleCommands(graph);

    return 0;
}

