#ifndef HUFFMAN_FUNCTIONS_H
#define HUFFMAN_FUNCTIONS_H

#include <array>
#include <unordered_map>
#include <string>
#include "huffman_structs.h"

// Build Huffman Tree
Node* buildHuffmanTree(const std::array<uint64_t, 256>& freq) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // Add all non-zero frequencies to the queue
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            pq.push(new Node(freq[i], i));
        }
    }

    // Special case: file is empty or contains 1 unique byte
    if (pq.empty()) {
        return nullptr;
    }
    if (pq.size() == 1) {
        // Duplicate the single node so tree has at least one branch
        Node* only = pq.top(); pq.pop();
        Node* dup = new Node(only->freq, only->byteValue);
        Node* parent = new Node(only->freq + dup->freq, -1, only, dup);
        return parent;
    }

    // Build tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node(left->freq + right->freq, -1, left, right);
        pq.push(parent);
    }

    return pq.top(); // root
}

// Generate Huffman Codes
std::unordered_map<int, std::string> generateHuffmanCodes(Node* root);

#endif

