#include "encrypt.h"

Encrypt::Encrypt() {}

Encrypt::~Encrypt() {}

bool Encrypt::encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& key) {
    // 构造 openssl enc 命令
    std::string opensslCommand = "openssl enc -aes-256-cbc -salt -in " + inputFilePath +
                                 " -out " + outputFilePath +
                                 " -k " + key;

    // 执行 openssl enc 命令
    int result = system(opensslCommand.c_str());

    if (result == 0) {
        std::cout << "Encryption successful." << std::endl;
    } else {
        std::cerr << "Encryption failed." << std::endl;
    }
    return result;
}

bool Encrypt::decryptFile(const std::string& inputFilePath,const std::string& outputFilePath,const std::string& key)
{
    // 构造 openssl enc 命令
    std::string opensslCommand = "openssl enc -d -aes-256-cbc -in " + inputFilePath +
                                 " -out " + outputFilePath +
                                 " -k " + key;

    // 执行 openssl enc 命令
    int result = system(opensslCommand.c_str());

    if (result == 0) {
        std::cout << "Decryption successful." << std::endl;
    } else {
        std::cerr << "Decryption failed." << std::endl;
    }
    return result;
}