#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <bitset>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#define ull unsigned long long

struct Node {
    unsigned char data;
    ull frequency;
    Node* left;
    Node* right;
    Node(unsigned char data, ull frequency)
        : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    Node(unsigned char data)
        : data(data), frequency(0), left(nullptr), right(nullptr) {}
};

struct NodeGreater {
    bool operator()(Node* a, Node* b) { return a->frequency > b->frequency; }
};

class Compress {
   public:
    std::string input_file;
    std::string output_file;

    Node* buildHuffmanTreeA(
        const std::unordered_map<unsigned char, ull>& frequency_map);
    Node* buildHuffmanTreeB(
        const std::unordered_map<unsigned char, std::string>& huffman_codes);
    void buildHuffmanCodes(
        Node* root,
        std::string code,
        std::unordered_map<unsigned char, std::string>& huffman_codes);

    Compress();

    ~Compress();

    bool compressFile(const std::string& input_file,
                      const std::string& output_file);
    bool decompressFile(const std::string& input_file,
                        const std::string& output_file);
};

#endif