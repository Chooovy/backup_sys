#include <iostream>
#include "compress.h"
#include "encrypt.h"
#include "tar.h"

int main()
{
    // Tar tarer;
    // tarer.pack("./tar_in", "./backup.tar");

    // Compress compressor;
    // compressor.compressFile("./backup.tar",
    //                         "./backup.tar.gz");
    Encrypt encrypter;
    // bool en = encrypter.encryptFile("./tar_in/1.bmp",
    //                                 "./backup.tar.gz.ec", "1");
    // std::cout << en << std::endl;

    // std::filesystem::path dir_path = "/home/thm/Desktop/backup_sys";
    // std::vector<std::string> file_names = {"backup.tar", "backup.tar.gz"};
    // for (const auto &file_name : file_names)
    // {
    //     std::filesystem::path file_path = dir_path / file_name;
    //     std::filesystem::remove(file_path);
    // }
    bool de = encrypter.decryptFile("./1.txt","./3.txt", "1");
    std::cout << de << std::endl;
    // compressor.decompressFile("./backup.tar.gz",
    //                           "./backup.tar");
    // tarer.unpack("./backup.tar", "/home/thm/Desktop/backup_sys/backup.tar");

    return 0;
}