#include "tar.h"
Tar::Tar(){}
Tar::~Tar(){}

bool Tar::pack(const std::string& input_path,const std::string& tar_file_name) {
    // 创建tar文件并打开以写入模式
    std::ofstream fout(tar_file_name, std::ios::out | std::ios::binary);
    if (!fout) {
        std::cerr << "Failed to open " << tar_file_name << std::endl;
        return false;
    }

    // 递归打包目录
    pack(input_path, fout);

    // 关闭tar文件
    fout.close();
    std::cout << "pack success" << std::endl;
    return true;
}

void Tar::pack(const std::filesystem::path& path, std::ofstream& fout) {
    if (is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string entry_path = entry.path().string();
            const std::string entry_name = entry.path().filename().string();

            struct posix_header* header = new struct posix_header;

            struct stat file_stat;

            if (entry.is_directory()) 
            {
                // 如果是目录，递归打包子目录
                getTarHeader(entry_path, entry_name, header, file_stat);
                pack(entry_path, fout);
            } 
            else 
            {
                // 如果是文件，打包文件内容
                std::ifstream fin(entry_path, std::ios::binary);

                if (!fin) 
                {
                    std::cerr << "Failed to open " << entry_path << std::endl;
                    continue;
                }

                getTarHeader(entry_path, entry_name, header, file_stat);

                tarWrite(fout, header);

                // 逐个字节地从输入文件读取内容并写入tar文件
                char buffer;
                int padding = 0;
                while (fin.get(buffer)) 
                {
                    fout.put(buffer);
                    padding += 1;
                }
                buffer = 0;
                while (padding % 512 != 0) 
                {
                    fout.put(buffer);
                    padding++;
                }

                fin.close();
            }
            delete header;
        }
        // 写入文件或目录结束的两个全0记录
        struct posix_header* end_header = new struct posix_header;
        tarWrite(fout, end_header);
        tarWrite(fout, end_header);
        delete end_header;
    }
    else {
        const std::string entry_path = path.string();
        const std::string entry_name = path.filename().string();

        struct posix_header* header = new struct posix_header;

        struct stat file_stat;
        // 如果是文件，打包文件内容

        std::ifstream fin(entry_path, std::ios::binary);
        if (!fin) {
            std::cerr << "Failed to open " << entry_path << std::endl;
            return;
        }

        getTarHeader(entry_path, entry_name, header, file_stat);

        tarWrite(fout, header);

        // 逐个字节地从输入文件读取内容并写入tar文件
        char buffer;
        int padding = 0;
        while (fin.get(buffer)) {
            fout.put(buffer);
            padding += 1;
        }
        buffer = 0;
        while (padding % 512 != 0) {
            fout.put(buffer);
            padding++;
        }

        fin.close();
        // 写入文件或目录结束的两个全0记录
        struct posix_header* end_header = new struct posix_header;
        tarWrite(fout, end_header);
        tarWrite(fout, end_header);
        delete end_header;
    }
}

void Tar::tarWrite(std::ofstream& fout, struct posix_header* header) {
    fout.write(header->name, sizeof(header->name));
    fout.write(header->mode, sizeof(header->mode));
    fout.write(header->uid, sizeof(header->uid));
    fout.write(header->gid, sizeof(header->gid));
    fout.write(header->size, sizeof(header->size));
    fout.write(header->mtime, sizeof(header->mtime));
    fout.write(header->chksum, sizeof(header->chksum));
    fout.write(header->typeflag, sizeof(header->typeflag));
    fout.write(header->linkname, sizeof(header->linkname));
    fout.write(header->magic, sizeof(header->magic));
    fout.write(header->version, sizeof(header->version));
    fout.write(header->uname, sizeof(header->uname));
    fout.write(header->gname, sizeof(header->gname));
    fout.write(header->devmajor, sizeof(header->devmajor));
    fout.write(header->devminor, sizeof(header->devminor));
    fout.write(header->prefix, sizeof(header->prefix));
    fout.write(header->padding, sizeof(header->padding));
}

int Tar::getChecksum(struct posix_header* header) {
    int chksum = 0;
    for (size_t i = 0; i < sizeof(header); ++i) {
        chksum += static_cast<int>(((char*)header)[i]);
    }
    return chksum;
}

void Tar::getTarHeader(const std::string entry_path,
                       const std::string entry_name,
                       struct posix_header* header,
                       struct stat file_stat) {
    if (stat(entry_path.c_str(), &file_stat) == 0) {
        strcpy(header->name, entry_name.c_str());

        snprintf(header->mode, sizeof(header->mode), "%07o",
                 (unsigned int)(file_stat.st_mode & 0777));

        snprintf(header->uid, sizeof(header->uid), "%07o",
                 (unsigned int)file_stat.st_uid);

        snprintf(header->gid, sizeof(header->gid), "%07o",
                 (unsigned int)file_stat.st_gid);

        if (S_ISDIR(file_stat.st_mode)) {
            sprintf(header->size, "%o", 0);  //是0x30还是0x00,补齐12个
        } else {
            off_t size = file_stat.st_size;
            // 将大小转换为八进制字符串
            sprintf(header->size, "%011o", (int)size);
        }

        snprintf(header->mtime, sizeof(header->mtime), "%011o",
                 (unsigned int)file_stat.st_mtime);

        char chksum[7];
        for (int i = 0; i < sizeof(header->chksum); i++) {
            chksum[i] = ' ';
            // chksum[i] = 0;
        }
        strcpy(header->chksum, chksum);

        header->typeflag[0] = ' ';
        if (S_ISREG(file_stat.st_mode)) {
            header->typeflag[1] = '0';  // 普通文件
        }
        // else if (S_ISLNK(file_stat.st_mode)) {
        //     header->typeflag = '1'; // 软链接
        // }
        else if (S_ISCHR(file_stat.st_mode)) {
            header->typeflag[1] = '3';  // 字符特殊文件
        } else if (S_ISBLK(file_stat.st_mode)) {
            header->typeflag[1] = '4';  // 块特殊文件
        } else if (S_ISDIR(file_stat.st_mode)) {
            header->typeflag[1] = '5';  // 目录
        } else if (S_ISFIFO(file_stat.st_mode)) {
            header->typeflag[1] = '6';  // FIFO特殊文件
        } else {
            header->typeflag[1] = '7';  // reserved
        }

        ssize_t bytesRead = readlink(entry_path.c_str(), header->linkname,
                                     sizeof(header->linkname) - 1);

        if (bytesRead != -1) {
            header->linkname[bytesRead] = '\0';  // 添加字符串终止符
        } else {
            strcpy(header->linkname, "");
        }

        // magic,version
        strcpy(header->magic, TMAGIC);
        header->version[0] = ' ';
        header->version[1] = ' ';
        header->version[2] = '\0';

        //--------------------------------------------------------------------------------------
        //获取uname
        //获取gname

        // //linux
        struct passwd* pw = getpwuid(file_stat.st_uid);
        struct group* gr = getgrgid(file_stat.st_gid);
        strcpy(header->uname, pw->pw_name);
        strcpy(header->gname, gr->gr_name);

        //---------------------------------------------------------------------------------------
        //获取devmajor
        //获取devminor

        // 获取设备文件的主要设备号和次要设备号
        // unsigned int devmajor = (unsigned int)major(file_stat.st_rdev);
        // unsigned int devminor = (unsigned int)minor(file_stat.st_rdev);

        // 以八进制字符串表示设备号
        // char file_devmajor[8]; // 足够存储八进制字符串的缓冲区
        // char file_devminor[8];

        // snprintf(file_devmajor, sizeof(file_devmajor), "%o", devmajor);
        // snprintf(file_devminor, sizeof(file_devminor), "%o", devminor);

        //获取prefix,完整路径除了文件名
        // char file_prefix[155];

        //要求得prefix前缀

        // create_tar_header(
        // &header, entry_name.c_str(), header->mode, header->uid, header->gid,
        // header->size, header->mtime, file_chksum, header->typeflag,
        // header->linkname, magic, version, file_uname, file_gname,
        // file_devmajor, file_devminor, file_prefix);

        //获取chksum
        snprintf(header->chksum, sizeof(header->chksum), "%06o",
                 (unsigned int)getChecksum(header));
    }
}

bool Tar::unpack(const std::string& output_path,
                 const std::string& tar_file_name) {
    std::ifstream fin(tar_file_name, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open " << tar_file_name << std::endl;
        return false;
    }
    bool is_valid_tar_file = isValidTarFile(fin);
    if (!is_valid_tar_file) {
        std::cout << "  it is not a valid tar file: " << tar_file_name
                  << std::endl;
        return false;
    }
    unpack(output_path, fin);
    fin.close();
    std::cout << "unpack success" << std::endl;
    return true;
}

bool Tar::isValidTarFile(std::ifstream& fin) {
    const int block_size{512};
    unsigned char buf[block_size];
    posix_header* header = (posix_header*)buf;
    memset(buf, 0, block_size);

    fin.seekg(0, std::ios::end);
    size = fin.tellg();
    fin.seekg(0, std::ios::beg);
    if (size % block_size != 0) {
        fprintf(stderr,
                "tar file size should be a multiple of 512 bytes: %ld\n", size);
        return false;
    }

    size_t pos{0};

    while (1) {
        fin.read(reinterpret_cast<char*>(buf), block_size);
        if (fin.gcount() != block_size)
            break;
        if (strncmp(header->magic, TMAGIC, 5))
            break;

        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count =
            (file_size + block_size - 1) / block_size;  //内容的占block数

        switch (header->typeflag[1]) {
            case '0':  // intentionally dropping through
            case '\0':
                // normal file
                file_sizes.push_back(file_size);
                file_names.push_back(std::string(header->name));
                file_data_start_addrs.push_back(pos);
                break;
            case '1':
                // hard link
                break;
            case '2':
                // symbolic link
                break;
            case '3':
                // device file/special file
                break;
            case '4':
                // block device
                break;
            case '5':
                // directory
                break;
            case '6':
                // named pipe
                break;
            default:
                break;
        }

        pos += file_block_count * block_size;
        fin.seekg(pos, std::ios::beg);
    }

    fin.seekg(0, std::ios::beg);

    return true;
}

std::vector<std::string> Tar::getFileNames() {
    return file_names;
}

bool Tar::getFileContents(const char* file_name,
                          char* contents,
                          std::ifstream& fin) {
    bool flag = false;
    for (int i = 0; i < file_names.size(); i++) {
        std::string name_(file_name);

        if (file_names[i].compare(name_) == 0) {
            int file_size = file_sizes[i];
            flag = true;
            // 移动文件指针到数据的开始位置
            fin.seekg(file_data_start_addrs[i], std::ios::beg);
            // 读取文件内容
            fin.read(contents, file_size);
            // 重置文件指针到文件开头
            fin.seekg(0, std::ios::beg);

            break;
        }
    }

    return flag;
}

size_t Tar::getFileSize(const char* file_name) {
    size_t file_size{0};

    for (int i = 0; i < file_names.size(); i++) {
        std::string name_(file_name);

        if (file_names[i].compare(name_) == 0) {
            file_size = file_sizes[i];
            break;
        }
    }

    return file_size;
}

size_t Tar::getTarSize() {
    return size;
}

void Tar::unpack(const std::string& output_path, std::ifstream& fin) {
    std::cout
        << "------------------------------------------------------------\n";
    fprintf(stderr, "tar file size: %ld byte\n", getTarSize());

    std::vector<std::string> file_names = getFileNames();
    fprintf(stderr, "tar file count: %ld\n", file_names.size());

    std::filesystem::create_directory(output_path);

    for (auto name : file_names) {
        std::ofstream fout(output_path + '/' + name,
                           std::ios::out | std::ios::binary);

        size_t file_size = getFileSize(name.c_str());
        fprintf(stderr, "file name: %s,  size: %ld byte\n", name.c_str(),
                file_size);

        char* contents = new char[file_size + 1];
        getFileContents(name.c_str(), contents, fin);
        contents[file_size] = '\0';

        for (int i = 0; i < file_size; i++) {
            fout.put(contents[i]);
        }
        fout.close();
        delete[] contents;
    }
    std::cout
        << "------------------------------------------------------------\n";
}

//打包上的比如checksum细节
//文件支持类型上的细节