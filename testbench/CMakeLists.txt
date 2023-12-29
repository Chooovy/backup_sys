# 添加头文件的路径
cmake_minimum_required(VERSION 3.10)
PROJECT(test1)

AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/../src" SRCS)
list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}" TEST_SRCS)
# 添加库
add_executable(test1 ${SRCS} ${TEST_SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ../include)
add_test(
    NAME mytest1
    COMMAND test1
)