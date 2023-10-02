#ifndef _DO_H_
#define _DO_H_

#include "tar.h"
#include "compress.h"
#include "encrypt.h"

class Do {
public:
    std::filesystem::path src_path; // 待备份的目录
    std::filesystem::path bak_path; // 备份文件路径(存放位置)
    std::filesystem::path tmp_path; // 存放临时文件的路径

    // BackupInfo info; // 备份信息
    // Filter filter;   // 用户自定义规则 过滤文件

    bool restore_metadata;  // 是否恢复文件元信息
    bool verbose;           // 是否输出执行过程信息


    Do(std::string src_path_, std::string bak_path_);
    ~Do();

    // void SetVerbose(bool verbose_);

    // 备份
    bool Backup(std::string password);
    // void SetComment(std::string comment_);
    // void SetMod(unsigned char mod_);
    // void SetFilter(const Filter &filter_);

    // 恢复
    bool Restore(std::string password);
    // void RestoreMetadata(bool restore_metadata_);
    // bool GetBackupInfo();
    // unsigned char GetBackupMode();

    // 获取备份文件的基本信息
    // static bool GetBackupInfo(std::string file_path_, BackupInfo &info_);
};

#endif