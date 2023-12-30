#ifndef INCLUDE_BACKUPMANAGER_H
#define INCLUDE_BACKUPMANAGER_H

#include <string>
#include <vector>

class BackupManager {
public:
    BackupManager(const std::string& sourceDir, const std::string& destDir);

    void setPathFilter(const std::string& pathFilter);
    void setNameFilter(const std::string& nameFilter);
    void setTypeFilter(const std::string& typeFilter);
    void setSizeFilter(long long sizeFilter);

    void customBackup();

private:
    std::string sourceDirectory;
    std::string destinationDirectory;
    std::string pathFilter;
    std::string nameFilter;
    std::string typeFilter;
    long long sizeFilter;

    void copyFile(const std::string& sourcePath, const std::string& destPath);
    bool applyFilters(const std::string& filePath) const;
    std::vector<std::string> getFilesToBackup() const;
};

#endif // BACKUPMANAGER_H