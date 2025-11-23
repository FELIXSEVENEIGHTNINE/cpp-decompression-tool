#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <queue>
#include <vector>
#include <cstdint>

#include "header/huffman_structs.h"
#include "header/huffman_functions.h"

// ---- Step 3: Generate codes ----

void generateCodes(Node* node, const std::string& prefix,
                   std::unordered_map<int, std::string>& codes)
{
    if (!node) return;

    // Leaf node = actual byte
    if (node->byteValue >= 0) {
        // If the file had only one unique character, assign "0"
        codes[node->byteValue] = prefix.empty() ? "0" : prefix;
        return;
    }

    // Traverse children
    generateCodes(node->left,  prefix + "0", codes);
    generateCodes(node->right, prefix + "1", codes);
}

std::unordered_map<int, std::string> generateHuffmanCodes(Node* root) {
    std::unordered_map<int, std::string> codes;
    generateCodes(root, "", codes);
    return codes;
}

//int main() {
//    // Example frequency table
//    std::array<uint64_t, 256> freq{};
//    freq.fill(0);
//    freq['A'] = 5;
//    freq['B'] = 9;
//    freq['C'] = 12;
//    freq['D'] = 13;
//    freq['E'] = 16;
//    freq['F'] = 45;
//
//    Node* root = buildHuffmanTree(freq);
//
//    // Map: byte -> bitstring
//    std::unordered_map<int, std::string> codes;
//    generateCodes(root, "", codes);
//
//    // Print all codes
//    std::cout << "Huffman Codes:\n";
//    for (auto& pair : codes) {
//        int byte = pair.first;
//        std::string code = pair.second;
//        std::cout << "'" << (char)byte << "' = " << code << "\n";
//    }
//}

