#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// 想测试什么模块就include什么模块
#include "compress.h"
#include <filesystem>

TEST_CASE("test1", "test_case1"){
    Compress comps;
    // std::filesystem::path currentpath = std::filesystem::current_path();
    // std::cout<< currentpath.string() << std::endl;
    // 测试文件输出在 build里面，这里的所有路径都是根据 build的相对路径
    bool cps = comps.compressFile("/home/george/projects/backup_sys/bin/helloworld.txt", "/home/george/projects/backup_sys/bin/helloworld.cps");
    REQUIRE(cps == true);
}