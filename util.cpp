#include "util.h"
#include <iostream>

void printUsage() {
    std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
}

bool isValidExecution(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return false;
    }
    return true;
}


