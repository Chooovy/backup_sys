#ifndef _DO_H_
#define _DO_H_

#include "tar.h"
#include "compress.h"
#include "encrypt.h"

class Do {
public:
    std::filesystem::path src_path; // �����ݵ�Ŀ¼
    std::filesystem::path bak_path; // �����ļ�·��(���λ��)
    std::filesystem::path tmp_path; // �����ʱ�ļ���·��

    // BackupInfo info; // ������Ϣ
    // Filter filter;   // �û��Զ������ �����ļ�

    bool restore_metadata;  // �Ƿ�ָ��ļ�Ԫ��Ϣ
    bool verbose;           // �Ƿ����ִ�й�����Ϣ


    Do(std::string src_path_, std::string bak_path_);
    ~Do();

    // void SetVerbose(bool verbose_);

    // ����
    bool Backup(std::string password);
    // void SetComment(std::string comment_);
    // void SetMod(unsigned char mod_);
    // void SetFilter(const Filter &filter_);

    // �ָ�
    bool Restore(std::string password);
    // void RestoreMetadata(bool restore_metadata_);
    // bool GetBackupInfo();
    // unsigned char GetBackupMode();

    // ��ȡ�����ļ��Ļ�����Ϣ
    // static bool GetBackupInfo(std::string file_path_, BackupInfo &info_);
};

#endif