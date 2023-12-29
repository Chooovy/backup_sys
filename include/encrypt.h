#include <openssl/evp.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define AES_BLOCK_SIZE 16

class Encrypt {
   public:
    std::string key;
    std::string input_file;
    std::string output_file;

    Encrypt();
    ~Encrypt();

    bool encryptFile(const std::string& input_file,
                     const std::string& output_file,
                     const std::string& key);
    bool decryptFile(const std::string& input_file,
                     const std::string& output_file,
                     const std::string& key);
};