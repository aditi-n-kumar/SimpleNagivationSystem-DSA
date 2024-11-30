#include "stack.h"

/*
int main() {
    Stack stack(10);
    // Add further tests or functionality as needed
    return 0;
}*/

Stack::Stack(int capacity) : top(-1), capacity(capacity) {
    elements = new pVERTEX[capacity];
}

Stack::~Stack() {
    delete[] elements;
}

void Stack::push(pVERTEX vertex) {
    if (top < capacity - 1) {
        elements[++top] = vertex;
    }
}

pVERTEX Stack::pop() {
    return isEmpty() ? nullptr : elements[top--];
}

bool Stack::isEmpty() const {
    return top == -1;
}


