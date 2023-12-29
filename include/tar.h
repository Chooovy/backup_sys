#ifndef _TAR_H_
#define _TAR_H_

#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "header.h"

class Tar {
   public:
    std::string input_path;
    std::string tar_file_name;

    bool verbose;
    size_t size;
    std::vector<std::string> file_names;
    std::vector<size_t> file_sizes;
    std::vector<size_t> file_data_start_addrs;

    Tar();
    ~Tar();
    bool pack(const std::string& input_path, const std::string& tar_file_name);
    void pack(const std::filesystem::path& path, std::ofstream& fout);
    void tarWrite(std::ofstream& fout, struct posix_header* header);
    int getChecksum(struct posix_header* header);
    void getTarHeader(const std::string entry_path,
                      const std::string entry_name,
                      struct posix_header* header,
                      struct stat file_stat);
    bool unpack(const std::string& output_path,
                const std::string& tar_file_name);
    void unpack(const std::string& output_path, std::ifstream& fin);
    bool isValidTarFile(std::ifstream& fin);
    std::vector<std::string> getFileNames();
    bool getFileContents(const char* file_name,
                         char* contents,
                         std::ifstream& fin);
    size_t getFileSize(const char* file_name);
    size_t getTarSize();
};

#endif