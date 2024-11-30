#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <cfloat>

enum COLOR { WHITE, GRAY, BLACK };

// Definition of the VERTEX structure
typedef struct TAG_VERTEX {
    int index;      // Unique identifier for the vertex
    COLOR color;    // Color of the vertex for BFS/DFS
    double key;     // Key value, usigng for Dijkstra's
    int pi;         // Predecessor index
    int position;   // Position in the heap
} VERTEX;

typedef VERTEX* pVERTEX;

typedef struct TAG_NODE {
    int index;      // Unique identifier for the node
    int u;          // Start vertex of the edge
    int v;          // End vertex of the edge
    double w;       // Weight of the edge
    TAG_NODE* next; // Pointer to the next node in the list
} NODE;


typedef NODE* pNODE;

#endif // DATA_STRUCTURES_H
