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

    //读取前16字节并解密以进行密码验证
    // if ((bytesRead = inFile.readsome(reinterpret_cast<char*>(inputBuffer), AES_BLOCK_SIZE)) != AES_BLOCK_SIZE) {
    //     EVP_CIPHER_CTX_free(ctx);
    //     std::cerr << "Invalid input file format." << std::endl;
    //     return false;
    // }

    // if (EVP_DecryptUpdate(ctx, outputBuffer, &decryptedBytes, inputBuffer, bytesRead) != 1) {
    //     EVP_CIPHER_CTX_free(ctx);
    //     return false;
    // }
    // std::cout << "Decrypted 16 bytes: ";
    // for (int i = 0; i < AES_BLOCK_SIZE; i++) {
    //     std::cout << std::hex << static_cast<int>(outputBuffer[i]);
    // }
    // std::cout << std::endl;
    // if (memcmp(key.c_str(), outputBuffer, AES_BLOCK_SIZE) != 0) {
    //     EVP_CIPHER_CTX_free(ctx);
    //     std::cerr << "Invalid password." << std::endl;
    //     return false;
    // }

    // 继续解密文件的其余部分
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
