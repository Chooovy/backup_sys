#include <openssl/evp.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> 
#define AES_BLOCK_SIZE 16

class Encrypt {
   public:
    std::string key;
    std::string input_file;
    std::string output_file;

    Encrypt();
    ~Encrypt();

    bool encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& key);
    bool decryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& key);
};