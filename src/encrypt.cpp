#include "encrypt.h"

Encrypt::Encrypt() {}

Encrypt::~Encrypt() {}

bool Encrypt::encryptFile(const std::string &input_file,
                          const std::string &output_file,
                          const std::string &key)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                           reinterpret_cast<const unsigned char *>(key.c_str()),
                           NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);

    if (!(fin && fout))
    {
        std::cerr << "Failed to open " << input_file << " or " << output_file << std::endl;
        return false;
    }

    const int BUFFER_SIZE = 4096;
    unsigned char input_buffer[BUFFER_SIZE];
    unsigned char output_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];

    int read_bytes;
    int encrypted_bytes;

    while ((read_bytes = fin.readsome(reinterpret_cast<char *>(input_buffer),
                                      BUFFER_SIZE)) > 0)
    {
        if (EVP_EncryptUpdate(ctx, output_buffer, &encrypted_bytes,
                              input_buffer, read_bytes) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
        fout.write(reinterpret_cast<const char *>(output_buffer),
                   encrypted_bytes);
    }

    if (EVP_EncryptFinal_ex(ctx, output_buffer, &encrypted_bytes) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    fout.write(reinterpret_cast<const char *>(output_buffer), encrypted_bytes);

    EVP_CIPHER_CTX_free(ctx);
    std::cout << "encryt success" << std::endl;
    return true;
}

bool Encrypt::decryptFile(const std::string &input_file,
                          const std::string &output_file,
                          const std::string &key)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                           reinterpret_cast<const unsigned char *>(key.c_str()),
                           NULL) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    std::ifstream fin(input_file, std::ios::binary);
    std::ofstream fout(output_file, std::ios::binary);

    if (!(fin && fout))
    {
        std::cerr << "Failed to open " << input_file << "or " << output_file << std::endl;
        return false;
    }

    const int BUFFER_SIZE = 4096;
    unsigned char input_buffer[BUFFER_SIZE];
    unsigned char output_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];

    int read_bytes;
    int decrypted_bytes;

    while ((read_bytes = fin.readsome(reinterpret_cast<char *>(input_buffer),
                                      BUFFER_SIZE)) > 0)
    {
        if (EVP_DecryptUpdate(ctx, output_buffer, &decrypted_bytes,
                              input_buffer, read_bytes) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            return false;
        }
        fout.write(reinterpret_cast<const char *>(output_buffer),
                   decrypted_bytes);
    }

    if (EVP_DecryptUpdate(ctx, output_buffer, &decrypted_bytes, input_buffer, read_bytes) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    fout.write(reinterpret_cast<const char *>(output_buffer), decrypted_bytes);

    if (EVP_DecryptFinal_ex(ctx, output_buffer, &decrypted_bytes) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        std::cout << "decrypt fail in final" << std::endl;
        return false;
    }
    fout.write(reinterpret_cast<const char *>(output_buffer), decrypted_bytes);

    EVP_CIPHER_CTX_free(ctx);
    std::cout << "decryt success" << std::endl;
    return true;
}
