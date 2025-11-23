#include <iostream>
#include <string>

#include "freq_table.cpp"
#include "huffman_codes.cpp"
#include "huffman_tree.cpp"
#include "compress.cpp"
#include "decompress.cpp"

#include "header/huffman_structs.h"
#include "header/huffman_functions.h"

std::string getDirectory(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    return (pos == std::string::npos) ? "." : path.substr(0, pos);
}

// Utility to get file extension
std::string getExtension(const std::string& path) {
    size_t pos = path.find_last_of('.');
    return (pos == std::string::npos) ? "" : path.substr(pos);
}

// Utility to get filename without directory
std::string getFilename(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}

int main() {
    std::string inputFile;
    std::cout << "Enter the file to process: ";
    std::cin >> inputFile;
    
    std::string dir = getDirectory(inputFile);
    std::string ext = getExtension(inputFile);
    std::string filename = getFilename(inputFile);
    
    std::string tempHuff = dir + "/temp_compressed.huff";
    std::string decompressedFile = dir + "/decompressed_" + filename;

    std::cout << "\nCalculating frequency table...\n";
    auto freq = calculateFrequency(inputFile);  // function from freq_table.cpp

    std::cout << "Building Huffman tree...\n";
    Node* root = buildHuffmanTree(freq);  // function from huffman_tree.cpp

    std::cout << "Generating Huffman codes...\n";
    auto codes = generateHuffmanCodes(root); // function from huffman_codes.cpp

//    std::cout << "\nHuffman codes for each byte in the file:\n";
//    for (auto &pair : codes) {
//        std::cout << (int)pair.first << " : " << pair.second << "\n";
//    }

	compressFile(inputFile, tempHuff, freq, codes);
	
	decompressFile(tempHuff, decompressedFile);
	
	if (std::remove(tempHuff.c_str()) == 0)
        std::cout << "Temporary compressed file deleted\n";
    else
        std::cerr << "Failed to delete temporary file\n";

    std::cout << "\nAll done! Decompressed file: " << decompressedFile << "\n";

    return 0;
}

