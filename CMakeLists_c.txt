cmake_minimum_required(VERSION 3.10)

# 项目名称
project(Backup_sys)

# 设置C++标准，例如C++11
set(CMAKE_CXX_STANDARD 17)

# 包含头文件目录
include_directories(include)

# 收集源文件
file(GLOB SOURCES "src/*.cpp")

# 查找OpenSSL
find_package(OpenSSL REQUIRED)

# 创建可执行文件
add_executable(backup_sys ${SOURCES})

# 添加链接openssl库
target_link_libraries(backup_sys OpenSSL::Crypto)

