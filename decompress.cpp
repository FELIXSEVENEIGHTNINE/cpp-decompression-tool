#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

#include "header/huffman_structs.h"
#include "header/huffman_functions.h"


void decompressFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream fin(inputPath, std::ios::binary);
    if (!fin) {
        std::cerr << "Cannot open input file\n";
        return;
    }

    // 1. Read header: 256 frequencies
    std::array<uint64_t, 256> freq{};
    for (int i = 0; i < 256; i++) {
        uint64_t f;
        fin.read(reinterpret_cast<char*>(&f), sizeof(uint64_t));
        freq[i] = f;
    }

    // 2. Rebuild Huffman tree
    Node* root = buildHuffmanTree(freq);
    if (!root) {
        std::cerr << "Input file is empty.\n";
        return;
    }

    // 3. Count total bytes to decode
    uint64_t totalBytes = 0;
    for (auto f : freq) totalBytes += f;

    // 4. Read bitstream and decode
    std::ofstream fout(outputPath, std::ios::binary);
    if (!fout) {
        std::cerr << "Cannot open output file\n";
        return;
    }

    Node* current = root;
    char byte;
    uint64_t decodedBytes = 0;

    while (fin.get(byte) && decodedBytes < totalBytes) {
        uint8_t bits = static_cast<uint8_t>(byte);
        for (int i = 7; i >= 0 && decodedBytes < totalBytes; i--) {
            bool bit = (bits >> i) & 1;
            current = bit ? current->right : current->left;

            if (current->byteValue >= 0) {
                fout.put(static_cast<char>(current->byteValue));
                current = root;
                decodedBytes++;
            }
        }
    }

    fin.close();
    fout.close();
    std::cout << "Decompression complete: " << outputPath << "\n";
}

// ---------------------
// Main
// ---------------------
//int main() {
//    std::string in, out;
//    std::cout << "Input compressed file (.huff): ";
//    std::cin >> in;
//    std::cout << "Output file: ";
//    std::cin >> out;
//
//    decompressFile(in, out);
//    return 0;
//}

