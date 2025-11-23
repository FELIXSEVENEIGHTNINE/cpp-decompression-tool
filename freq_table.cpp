#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <iomanip>

// Function to calculate frequency table from a file
std::array<uint64_t, 256> calculateFrequency(const std::string& input_path) {
    std::ifstream fin(input_path, std::ios::binary);
    if (!fin) {
        std::cerr << "Error: cannot open file " << input_path << "\n";
        return {}; // return empty array on error
    }

    std::array<uint64_t, 256> freq{};
    freq.fill(0);

    const std::size_t BUF_SIZE = 1 << 20; // 1 MiB
    std::vector<char> buffer(BUF_SIZE);

    while (fin) {
        fin.read(buffer.data(), static_cast<std::streamsize>(BUF_SIZE));
        std::streamsize n = fin.gcount();
        for (std::streamsize i = 0; i < n; ++i) {
            unsigned char b = static_cast<unsigned char>(buffer[i]);
            ++freq[b];
        }
    }

    return freq;
}

// Optional helper to print frequencies
void printFrequency(const std::array<uint64_t, 256>& freq, const std::string& input_path) {
    uint64_t total = 0;
    for (auto v : freq) total += v;

    std::cout << "File: " << input_path << "\n";
    std::cout << "Total bytes: " << total << "\n\n";
    std::cout << "Byte  Frequency\n";
    std::cout << "----  ---------\n";
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            std::cout << std::setw(3) << i << "   " << freq[i];
            if (i >= 32 && i <= 126) {
                std::cout << "    ('" << static_cast<char>(i) << "')";
            }
            std::cout << "\n";
        }
    }
}

