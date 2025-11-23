#include <iostream>
#include <fstream>
#include <unordered_map>
#include <array>
#include <vector>
#include <queue>
#include <string>
#include <cstdint>

#include "header/huffman_structs.h"
#include "header/huffman_functions.h"

void compressFile(const std::string& inputPath, const std::string& outputPath, std::array<uint64_t, 256>& outFreq, std::unordered_map<int, std::string>& outCodes)
{
    // 1. Read file & count frequencies
    std::ifstream fin(inputPath, std::ios::binary);
    if (!fin) {
        std::cerr << "Cannot open input file\n";
        return;
    }

    std::array<uint64_t, 256> freq{};
    freq.fill(0);

    std::vector<unsigned char> bytes;
    char c;
    while (fin.get(c)) {
        bytes.push_back((unsigned char)c);
        freq[(unsigned char)c]++;
    }
    fin.close();

    if (bytes.empty()) {
        std::cerr << "Input file is empty.\n";
        return;
    }

    // 2. Build tree & generate codes
    Node* root = buildHuffmanTree(freq);
    std::unordered_map<int, std::string> codes;
    generateCodes(root, "", codes);

    // 3. Open output file
    std::ofstream fout(outputPath, std::ios::binary);
    if (!fout) {
        std::cerr << "Cannot open output file\n";
        return;
    }

    // 4. Write header: 256 frequencies (8 bytes each)
    for (int i = 0; i < 256; i++) {
        uint64_t f = freq[i];
        fout.write(reinterpret_cast<char*>(&f), sizeof(uint64_t));
    }

    // 5. Encode file into bits
    uint8_t bitBuffer = 0;
    int bitCount = 0;

    for (unsigned char b : bytes) {
        const std::string& code = codes[b];
        for (char bit : code) {
            bitBuffer <<= 1;
            if (bit == '1')
                bitBuffer |= 1;

            bitCount++;

            if (bitCount == 8) {
                fout.put(bitBuffer);
                bitBuffer = 0;
                bitCount = 0;
            }
        }
    }

    // Flush leftover bits (pad with zeros)
    if (bitCount > 0) {
        bitBuffer <<= (8 - bitCount);
        fout.put(bitBuffer);
    }

    fout.close();
    std::cout << "Compression complete: " << outputPath << "\n";
}

// ---------------------
// Main
// ---------------------
//int main() {
//    std::string in, out;
//    std::cout << "Input file: ";
//    std::cin >> in;
//    std::cout << "Output file (.huff): ";
//    std::cin >> out;
//
//    compressFile(in, out);
//    return 0;
//}

