#include "heap.h"
#include <iostream>
#include <cmath>
#include <unordered_map>

MinHeap::MinHeap(int cap) : limit(cap), size(0) {
    if (limit <= 0) {
        throw std::invalid_argument("Heap capacity must be positive.");
    }
    H = new pVERTEX[cap + 1];
    position = new int[cap + 1]; // Track positions
    for (int i = 1; i <= cap; ++i) {
        position[i] = -1; // Initialize to invalid
    }
}

MinHeap::~MinHeap() {
    delete[] H;
    delete[] position;
}

void MinHeap::insert(pVERTEX vertex) {
    if (size == limit) {
        std::cerr << "Heap overflow\n";
        return;
    }
    size++;
    int i = size;
    H[i] = vertex;
    position[vertex->index] = i; // Track position

    while (i > 1 && H[i / 2]->key > H[i]->key) {
        std::swap(H[i], H[i / 2]);
        std::swap(position[H[i]->index], position[H[i / 2]->index]);
        i /= 2;
    }
}

pVERTEX MinHeap::extractMinimum() {
    if (size == 0) {
        std::cerr << "Heap underflow\n";
        return nullptr;
    }
    pVERTEX min = H[1];
    position[min->index] = -1; // Remove from position tracking
    H[1] = H[size];
    position[H[1]->index] = 1; // Update position
    size--;
    minHeapify(1);
    return min;
}

void MinHeap::decreaseKey(int vertexIndex, double newKey) {
    int idx = position[vertexIndex]; // Get heap index from position map
    if (idx < 1 || idx > size) {
        std::cerr << "Invalid heap index for vertex: " << vertexIndex << "\n";
        return;
    }
    H[idx]->key = newKey;
    while (idx > 1 && H[idx / 2]->key > H[idx]->key) {
        std::swap(H[idx], H[idx / 2]);
        std::swap(position[H[idx]->index], position[H[idx / 2]->index]);
        idx /= 2;
    }
}

void MinHeap::minHeapify(int idx) {
    int small = idx;
    int left = 2 * idx;
    int right = 2 * idx + 1;

    if (left <= size && H[left]->key < H[small]->key) {
        small = left;
    }
    if (right <= size && H[right]->key < H[small]->key) {
        small = right;
    }
    if (small != idx) {
        std::swap(H[idx], H[small]);
        std::swap(position[H[idx]->index], position[H[small]->index]);
        minHeapify(small);
    }
}

bool MinHeap::isEmpty() const {
    return size == 0;
}
