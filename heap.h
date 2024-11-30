#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

class MinHeap {
public:
    int limit;
    int size;
    pVERTEX* H;
    int* position; // Tracks the position of each vertex in the heap

    MinHeap(int cap);
    ~MinHeap();
    void insert(pVERTEX vertex);
    pVERTEX extractMinimum();
    void decreaseKey(int index, double newKey);
    bool isEmpty() const;
    void minHeapify(int index);
};

#endif // HEAP_H
