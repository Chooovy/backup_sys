#ifndef _TAR_H_
#define _TAR_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include "header.h"

class Tar {
    public:
        std::string inputpath;
        std::string tarfilename;
        // const char* inputPath;
        // const char* tarFileName;

        bool verbose;
        size_t size;
        std::vector<std::string> file_names;
        std::vector<size_t> file_sizes;
        std::vector<size_t> file_data_start_addrs;

        Tar(const std::string& inputpath_, const std::string& tarfilename_);
        ~Tar();
        bool Pack();
        void pack(const std::filesystem::path& path, std::ofstream& tarFile);
        void tar_write(std::ofstream& tarFile,struct posix_header* header);
        int get_chksum(struct posix_header* header);
        void get_tar_header(const std::string entryPath, const std::string entryName, struct posix_header* header, struct stat fileStat);
        bool Unpack();
        void unpack(std::ifstream& tarFile);
        bool IsValidTarFile(std::ifstream& tarFile);
        std::vector<std::string> GetFileNames();
        bool GetFileContents(const char* file_name, char* contents, std::ifstream& tarFile);
        size_t GetFileSize(const char* file_name);
        size_t GetTarSize();
};

#endif