cmake_minimum_required(VERSION 3.10)

# 项目名称
project(Backup_sys)

# 设置C++标准，例如C++17
set(CMAKE_CXX_STANDARD 17)

# 启用调试信息
set(CMAKE_BUILD_TYPE Debug)

# 可执行文件和库文件存放路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/openssl)

# 编译动态库
add_library(tar SHARED src/tar.cpp)
add_library(compress SHARED src/compress.cpp)
add_library(encrypt SHARED src/encrypt.cpp)

# 收集源文件
set(SOURCES src/main.cpp)

# 增加链接库位置
set(LIB tar compress encrypt)

# 创建可执行文件
add_executable(main ${SOURCES})

# 静态链接openssl库
find_library(SSL ssl ${PROJECT_SOURCE_DIR}/lib)
find_library(CRYPTO crypto ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(encrypt ${SSL} ${CRYPTO})

# 添加链接动态库
target_link_libraries(main ${LIB})