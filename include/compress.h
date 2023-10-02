#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>

#define ull unsigned long long

struct Node {
    unsigned char data;
    ull frequency;
    Node* left;
    Node* right;
    Node(unsigned char data, ull frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    Node(unsigned char data) : data(data), frequency(0), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

class Compress {
    public:
        std::string inputFile;
        std::string compressedFile;
        std::string outputFile;

        Node* buildHuffmanTree_a(const std::unordered_map<unsigned char, ull>& frequencyMap);
        Node* buildHuffmanTree_b(const std::unordered_map<unsigned char, std::string>& huffmanCodes);
        void buildHuffmanCodes(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& huffmanCodes);


        Compress();
        // Compress(std::string inputFile_, std::string compressedFile_, std::string outputFile_);
        ~Compress();

        bool compressFile(const std::string& inputFile, const std::string& compressedFile);
        bool decompressFile(const std::string& compressedFile, const std::string& outputFile);

};

#endif