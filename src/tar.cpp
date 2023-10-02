#include "tar.h"

Tar::Tar(const std::string& inputpath_, const std::string& tarfilename_) {
    inputpath = inputpath_;
    tarfilename = tarfilename_;
}


Tar::~Tar() {

}

bool Tar::Pack() {
    // ����tar�ļ�������д��ģʽ
    std::ofstream tarFile(tarfilename, std::ios::out | std::ios::binary);
    if (!tarFile) {
        std::cerr << "Failed to open " << tarfilename << "in_tar.cpp_17" << std::endl;
        return false;
    }

    // �ݹ���Ŀ¼
    pack(inputpath, tarFile);

    // �ر�tar�ļ�
    tarFile.close();
    std::cout << "pack success" << std::endl;
    return true;
}

void Tar::pack(const std::filesystem::path& path, std::ofstream& tarFile) {
    if (is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string entryPath = entry.path().string();
            const std::string entryName = entry.path().filename().string();

            struct posix_header* header = new struct posix_header;

            struct stat fileStat;

            if (entry.is_directory()) {
                // �����Ŀ¼���ݹ�����Ŀ¼
                get_tar_header(entryPath, entryName, header, fileStat);
                pack(entryPath, tarFile);
            } else {
                // ������ļ�������ļ�����
                std::ifstream inputFile(entryPath, std::ios::binary);

                if (!inputFile) {
                    std::cerr << "Failed to open " << entryPath << "in_tar.cpp_51" << std::endl;
                    continue;
                }

                get_tar_header(entryPath, entryName, header, fileStat);

                // tarFile.write(reinterpret_cast<char*>(header), sizeof(header));
                tar_write(tarFile, header);

                // ����ֽڵش������ļ���ȡ���ݲ�д��tar�ļ�
                char buffer;
                int padding = 0;
                while (inputFile.get(buffer)) {
                    tarFile.put(buffer);
                    padding += 1;
                }
                buffer = 0;
                while (padding%512 != 0) {
                    tarFile.put(buffer);
                    padding ++;
                }

                inputFile.close();
            }
            delete header;
        }
        // д���ļ���Ŀ¼����������ȫ0��¼
        struct posix_header* endHeader = new struct posix_header;
        // tarFile.write(reinterpret_cast<char*>(&endHeader), sizeof(endHeader));
        // tarFile.write(reinterpret_cast<char*>(&endHeader), sizeof(endHeader));
        tar_write(tarFile, endHeader);
        tar_write(tarFile, endHeader);
        delete endHeader;
    }
    else {
        const std::string entryPath = path.string();
        const std::string entryName = path.filename().string();

        struct posix_header* header = new struct posix_header;

        struct stat fileStat;
        // ������ļ�������ļ�����
        
        std::ifstream inputFile(entryPath, std::ios::binary);
        if (!inputFile) {
            std::cerr << "Failed to open " << entryPath << " in_tar.cpp_96" << std::endl;
            return;
        }

        get_tar_header(entryPath, entryName, header, fileStat);

        // tarFile.write(reinterpret_cast<char*>(header), sizeof(header));
        tar_write(tarFile, header);

        // ����ֽڵش������ļ���ȡ���ݲ�д��tar�ļ�
        char buffer;
        int padding = 0;
        while (inputFile.get(buffer)) {
            tarFile.put(buffer);
            padding += 1;
        }
        buffer = 0;
        while (padding%512 != 0) {
            tarFile.put(buffer);
            padding ++;
        }

        inputFile.close();
        // д���ļ���Ŀ¼����������ȫ0��¼
        struct posix_header* endHeader = new struct posix_header;
        // tarFile.write(reinterpret_cast<char*>(&endHeader), sizeof(endHeader));
        // tarFile.write(reinterpret_cast<char*>(&endHeader), sizeof(endHeader));
        tar_write(tarFile, endHeader);
        tar_write(tarFile, endHeader);
        delete endHeader;
    }
}

void Tar::tar_write(std::ofstream& tarFile,struct posix_header* header) {
    tarFile.write(header->name,        sizeof(header->name)     );
    tarFile.write(header->mode,        sizeof(header->mode)     );
    tarFile.write(header->uid,         sizeof(header->uid)      );
    tarFile.write(header->gid,         sizeof(header->gid)      );
    tarFile.write(header->size,        sizeof(header->size)     );
    tarFile.write(header->mtime,       sizeof(header->mtime)    );
    tarFile.write(header->chksum,      sizeof(header->chksum)   );
    tarFile.write(header->typeflag,    sizeof(header->typeflag) );
    // tarFile.put(header->typeflag);
    tarFile.write(header->linkname,    sizeof(header->linkname) );
    tarFile.write(header->magic,       sizeof(header->magic)    );
    tarFile.write(header->version,     sizeof(header->version)  );
    tarFile.write(header->uname,       sizeof(header->uname)    );
    tarFile.write(header->gname,       sizeof(header->gname)    );
    tarFile.write(header->devmajor,    sizeof(header->devmajor) );
    tarFile.write(header->devminor,    sizeof(header->devminor) );
    tarFile.write(header->prefix,      sizeof(header->prefix)   );
    tarFile.write(header->padding,     sizeof(header->padding)  );
}

int Tar::get_chksum(struct posix_header* header) {
    int chksum = 0;
    for (size_t i = 0; i < sizeof(header); ++i) {
        chksum += static_cast<int>( ( (char*)header )[i] );
    }
    return chksum;
}

void Tar::get_tar_header(const std::string entryPath, const std::string entryName, struct posix_header* header, struct stat fileStat) {

    if ( stat( entryPath.c_str(), &fileStat) == 0 ) {
        strcpy(header->name, entryName.c_str());

        snprintf(header->mode, sizeof(header->mode), "%07o", (unsigned int)(fileStat.st_mode & 0777));

        snprintf(header->uid, sizeof(header->uid), "%07o", (unsigned int)fileStat.st_uid);

        snprintf(header->gid, sizeof(header->gid), "%07o", (unsigned int)fileStat.st_gid);

        if (S_ISDIR(fileStat.st_mode)) {
            sprintf(header->size, "%o", 0);//��0x30����0x00,����12��
        } else {
            off_t size = fileStat.st_size;
            // ����Сת��Ϊ�˽����ַ���
            sprintf(header->size, "%011o", (int)size);
        }

        snprintf(header->mtime, sizeof(header->mtime), "%011o", (unsigned int)fileStat.st_mtime);

        char chksum[7];
        for (int i=0 ; i < sizeof(header->chksum); i++) {
            chksum[i]=' ';
            // chksum[i] = 0;
        }
        strcpy(header->chksum, chksum);

        header->typeflag[0] = ' ';
        if (S_ISREG(fileStat.st_mode)) {
            header->typeflag[1] = '0'; // ��ͨ�ļ�
        }
            // else if (S_ISLNK(fileStat.st_mode)) {
            //     header->typeflag = '1'; // ������
            // }
        else if (S_ISDIR(fileStat.st_mode)) {
            header->typeflag[1] = '5'; // Ŀ¼
        } else if (S_ISCHR(fileStat.st_mode)) {
            header->typeflag[1] = '3'; // �ַ������ļ�
        } else if (S_ISBLK(fileStat.st_mode)) {
            header->typeflag[1] = '4'; // �������ļ�
        } else if (S_ISFIFO(fileStat.st_mode)) {
            header->typeflag[1] = '6'; // FIFO�����ļ�
        } else {
            header->typeflag[1] = '7'; // reserved
        }

        ssize_t bytesRead = readlink(entryPath.c_str(), header->linkname, sizeof(header->linkname) - 1);

        if (bytesRead != -1) {
            header->linkname[bytesRead] = '\0'; // ����ַ�����ֹ��
        } else {
            strcpy(header->linkname,"");
        }

        //magic,version
        strcpy(header->magic, TMAGIC);
        header->version[0] = ' ';
        header->version[1] = ' ';
        header->version[2] = '\0';

//--------------------------------------------------------------------------------------
        //��ȡuname
        //��ȡgname

        // //linux
        struct passwd *pw = getpwuid(fileStat.st_uid);
        struct group *gr = getgrgid(fileStat.st_gid);
        strcpy(header->uname, pw->pw_name);
        strcpy(header->gname, gr->gr_name);

//---------------------------------------------------------------------------------------
        //��ȡdevmajor
        //��ȡdevminor

        // ��ȡ�豸�ļ�����Ҫ�豸�źʹ�Ҫ�豸��
        // unsigned int devmajor = (unsigned int)major(fileStat.st_rdev);
        // unsigned int devminor = (unsigned int)minor(fileStat.st_rdev);

        // �԰˽����ַ�����ʾ�豸��
        // char file_devmajor[8]; // �㹻�洢�˽����ַ����Ļ�����
        // char file_devminor[8];

        // snprintf(file_devmajor, sizeof(file_devmajor), "%o", devmajor);
        // snprintf(file_devminor, sizeof(file_devminor), "%o", devminor);


        //��ȡprefix,����·�������ļ���
        // char file_prefix[155];

        //Ҫ���prefixǰ׺

        // create_tar_header(
        // &header, entryName.c_str(), header->mode, header->uid, header->gid, header->size, header->mtime,
        // file_chksum, header->typeflag, header->linkname, magic, version, file_uname, file_gname,
        // file_devmajor, file_devminor, file_prefix);

        //��ȡchksum
        snprintf(header->chksum, sizeof(header->chksum), "%06o", (unsigned int)get_chksum(header));
    }
}

bool Tar::Unpack() {
    std::ifstream tarFile(tarfilename, std::ios::in | std::ios::binary);
    if (!tarFile) {
        std::cerr << "Failed to open " << tarfilename << "in_tar.cpp_263" << std::endl;
        return false;
    }
    unpack(tarFile);
    tarFile.close();
    std::cout << "unpack success" << std::endl;
    return true;
}

bool Tar::IsValidTarFile(std::ifstream& tarFile)
{
    if (!tarFile.is_open()) {
        std::cerr << "Failed to open" << tarfilename << "in_tar.cpp_275" << std::endl;
        return false;
    }

    const int block_size{ 512 };
    unsigned char buf[block_size];
    posix_header* header = (posix_header*)buf;
    memset(buf, 0, block_size);

    tarFile.seekg(0, std::ios::end);
    size = tarFile.tellg();
    tarFile.seekg(0, std::ios::beg);
    if (size % block_size != 0) {
        fprintf(stderr, "tar file size should be a multiple of 512 bytes: %ld\n", size);
        return false;
    }

    size_t pos{ 0 };

    while (1) {
        tarFile.read(reinterpret_cast<char*>(buf), block_size);
        if (tarFile.gcount() != block_size) break;
        if (strncmp(header->magic, TMAGIC, 5)) break;

        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;//���ݵ�ռblock��

        switch (header->typeflag[1]) {
            case '0': // intentionally dropping through
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
        tarFile.seekg(pos, std::ios::beg);
    }

    tarFile.seekg(0, std::ios::beg);

    return true;
}

std::vector<std::string> Tar::GetFileNames()
{
    return file_names;
}

bool Tar::GetFileContents(const char* file_name, char* contents, std::ifstream& tarFile)
{
    bool flag = false;
    for (int i = 0; i < file_names.size(); i++) {
        std::string name_(file_name);

        if (file_names[i].compare(name_) == 0) {
            int file_size = file_sizes[i];
            flag = true;
            // �ƶ��ļ�ָ�뵽���ݵĿ�ʼλ��
            tarFile.seekg(file_data_start_addrs[i], std::ios::beg);
            // ��ȡ�ļ�����
            tarFile.read(contents, file_size);
            // �����ļ�ָ�뵽�ļ���ͷ
            tarFile.seekg(0, std::ios::beg);

            break;
        }
    }

    return flag;
}

size_t Tar::GetFileSize(const char* file_name)
{
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

size_t Tar::GetTarSize()
{
    return size;
}

void Tar::unpack(std::ifstream& tarFile)
{
    bool is_valid_tar_file = IsValidTarFile(tarFile);
    if (!is_valid_tar_file) {
        // fprintf(stderr, "it is not a valid tar file: %s\n", tarfilename);
        std::cout << "  it is not a valid tar file: " << tarfilename << std::endl;
        return;
    }
    std::cout << "------------------------------------------------------------\n";
    fprintf(stderr, "tar file size: %ld byte\n", GetTarSize());

    std::vector<std::string> file_names = GetFileNames();
    fprintf(stderr, "tar file count: %ld\n", file_names.size());

    for (auto name : file_names) {

        // const char* orgFileName = (inputpath + '/' + name).c_str();//tar�ļ��ĵ�ַ
        std::ofstream orgFile(inputpath + '/' + name, std::ios::out | std::ios::binary);

        size_t file_size = GetFileSize(name.c_str());
        fprintf(stderr, "file name: %s,  size: %ld byte\n", name.c_str(), file_size);

        char* contents = new char[file_size + 1];
        GetFileContents(name.c_str(), contents, tarFile);
        contents[file_size] = '\0';

        // fprintf(stderr, "contents:\n%s\n", contents);
        for(int i=0; i < file_size; i++) {
            orgFile.put(contents[i]);
        }
        orgFile.close();
        delete[] contents;
    }
    std::cout << "------------------------------------------------------------\n";
}

//����ϵı���checksumϸ��
//�ļ�֧�������ϵ�ϸ��
//filebak���һ��������ԸĽ�