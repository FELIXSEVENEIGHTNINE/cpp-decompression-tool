#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <cstdint>

#include "header/huffman_structs.h"
#include "header/huffman_functions.h"


// Recursively print tree (for debugging)
void printTree(Node* node, const std::string& prefix = "") {
    if (!node) return;

    if (node->byteValue >= 0) {
        std::cout << prefix << "Leaf: byte=" << node->byteValue
                  << " freq=" << node->freq << "\n";
    } else {
        std::cout << prefix << "Internal freq=" << node->freq << "\n";
    }

    printTree(node->left, prefix + "  ");
    printTree(node->right, prefix + "  ");
}

//int main() {
//    // Example frequency table (you will replace this with Step 1 data)
//    std::array<uint64_t, 256> freq{};
//    freq.fill(0);
//
//    freq['A'] = 5;
//    freq['B'] = 9;
//    freq['C'] = 12;
//    freq['D'] = 13;
//    freq['E'] = 16;
//    freq['F'] = 45;
//
//    Node* root = buildHuffmanTree(freq);
//
//    if (root) {
//        std::cout << "Huffman Tree:\n";
//        printTree(root);
//    } else {
//        std::cout << "Tree is empty (no input)\n";
//    }
//
//    return 0;
//}

