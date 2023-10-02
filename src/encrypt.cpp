#include "encrypt.h"
//-lssl -lcrypto
// 加密函数

Encrypt::Encrypt() {

}

Encrypt::~Encrypt() {
    
}

bool Encrypt::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                          reinterpret_cast<const unsigned char*>(key.c_str()), NULL) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    const int bufferSize = 4096;
    unsigned char inputBuffer[bufferSize];
    unsigned char outputBuffer[bufferSize + EVP_MAX_BLOCK_LENGTH];

    int bytesRead;
    int encryptedBytes;

    while ((bytesRead = inFile.readsome(reinterpret_cast<char*>(inputBuffer), bufferSize)) > 0) {
        if (EVP_EncryptUpdate(ctx, outputBuffer, &encryptedBytes, inputBuffer, bytesRead) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
        outFile.write(reinterpret_cast<const char*>(outputBuffer), encryptedBytes);
    }

    if (EVP_EncryptFinal_ex(ctx, outputBuffer, &encryptedBytes) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    outFile.write(reinterpret_cast<const char*>(outputBuffer), encryptedBytes);

    EVP_CIPHER_CTX_free(ctx);
    std::cout << "encryt success" << std::endl;
    return true;
}

// 解密函数
bool Encrypt::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                          reinterpret_cast<const unsigned char*>(key.c_str()), NULL) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    const int bufferSize = 4096;
    unsigned char inputBuffer[bufferSize];
    unsigned char outputBuffer[bufferSize + EVP_MAX_BLOCK_LENGTH];

    int bytesRead;
    int decryptedBytes;

    while ((bytesRead = inFile.readsome(reinterpret_cast<char*>(inputBuffer), bufferSize)) > 0) {
        if (EVP_DecryptUpdate(ctx, outputBuffer, &decryptedBytes, inputBuffer, bytesRead) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
        outFile.write(reinterpret_cast<const char*>(outputBuffer), decryptedBytes);
    }

    if (EVP_DecryptFinal_ex(ctx, outputBuffer, &decryptedBytes) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    outFile.write(reinterpret_cast<const char*>(outputBuffer), decryptedBytes);

    EVP_CIPHER_CTX_free(ctx);
    std::cout << "decryt success" << std::endl;
    return true;
}

// int main() {
//     std::string inputFile = "./1.txt"; // 替换为你的输入文件
//     std::string encryptedFile = "./encrypted.bin"; // 替换为加密后的输出文件
//     std::string decryptedFile = "./decrypted.txt"; // 替换为解密后的输出文件
//     std::string key = "5464"; // 替换为你的加密密钥

//     // 加密文件
//     if (encryptFile(inputFile, encryptedFile, key)) {
//         std::cout << "File is encrypted." << std::endl;
//     } else {
//         std::cerr << "Fail to encrypt" << std::endl;
//     }

//     // 解密文件
//     if (decryptFile(encryptedFile, decryptedFile, key)) {
//         std::cout << "File is decrypted." << std::endl;
//     } else {
//         std::cerr << "Fail to decrypt." << std::endl;
//     }

//     return 0;
// }
