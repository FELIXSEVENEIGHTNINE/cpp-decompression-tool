#ifndef HUFFMAN_STRUCTS_H
#define HUFFMAN_STRUCTS_H

#include <cstdint>

struct Node {
    uint64_t freq;
    int byteValue;
    Node* left;
    Node* right;
    Node(uint64_t f, int b = -1, Node* l = nullptr, Node* r = nullptr)
        : freq(f), byteValue(b), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) const { return a->freq > b->freq; }
};

#endif

