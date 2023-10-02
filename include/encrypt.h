#include <iostream>
#include <fstream>
#include <string>
#include <openssl/evp.h>
#include <cstring>

#define AES_BLOCK_SIZE 16

class Encrypt {
    public:
        std::string key;
        std::string inputFile;
        std::string encryptedFile;
        std::string outputFile;

        Encrypt();
        ~Encrypt();

        bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
        bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
};