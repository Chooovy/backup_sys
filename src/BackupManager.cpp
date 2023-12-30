#include "BackupManager.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

BackupManager::BackupManager(const std::string& sourceDir, const std::string& destDir)
    : sourceDirectory(sourceDir), destinationDirectory(destDir), sizeFilter(-1) {}

void BackupManager::setPathFilter(const std::string& pathFilter) {
    this->pathFilter = pathFilter;
}

void BackupManager::setNameFilter(const std::string& nameFilter) {
    this->nameFilter = nameFilter;
}

void BackupManager::setTypeFilter(const std::string& typeFilter) {
    this->typeFilter = typeFilter;
}

void BackupManager::setSizeFilter(long long sizeFilter) {
    this->sizeFilter = sizeFilter;
}

void BackupManager::customBackup() {
    if (!fs::exists(destinationDirectory)) {
        std::cerr << "Destination directory does not exist." << std::endl;
        return;
    }

    // Create a subdirectory for the backup with the current date and time
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
    std::string backupSubDir = ss.str();
    std::string backupPath = destinationDirectory + fs::path::preferred_separator + backupSubDir;
    fs::create_directories(backupPath);

    // Iterate through files in the source directory and copy them to the backup directory
    for (const auto& filePath : getFilesToBackup()) {
        std::string sourceFilePath = sourceDirectory + fs::path::preferred_separator + filePath;
        std::string destFilePath = backupPath + fs::path::preferred_separator + fs::path(filePath).filename().string();

        copyFile(sourceFilePath, destFilePath);

        std::cout << "Copied: " << sourceFilePath << " -> " << destFilePath << std::endl;
    }

    std::cout << "Backup completed. Files are backed up to: " << backupPath << std::endl;
}

void BackupManager::copyFile(const std::string& sourcePath, const std::string& destPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    std::ofstream destFile(destPath, std::ios::binary);
    destFile << sourceFile.rdbuf();
}

bool BackupManager::applyFilters(const std::string& filePath) const {
    if (!pathFilter.empty() && filePath.find(pathFilter) == std::string::npos) {
        return false;
    }

    if (!nameFilter.empty() && fs::path(filePath).filename().string().find(nameFilter) == std::string::npos) {
        return false;
    }

    if (!typeFilter.empty() && fs::path(filePath).extension().string() != typeFilter) {
        return false;
    }

    if (sizeFilter != -1) {
        std::error_code ec;
        auto fileSize = fs::file_size(filePath, ec);
        if (!ec && fileSize > sizeFilter) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> BackupManager::getFilesToBackup() const {
    std::vector<std::string> filesToBackup;

    for (const auto& entry : fs::recursive_directory_iterator(sourceDirectory)) {
        if (fs::is_regular_file(entry)) {
            std::string filePath = entry.path().string();

            if (applyFilters(filePath)) {
                filesToBackup.push_back(filePath);
            }
        }
    }

    return filesToBackup;
}
