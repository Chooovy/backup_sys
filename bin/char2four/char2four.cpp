#include <iostream>
#include <string>
#include <filesystem>
int main() {
    // 假设 filepath 是一个 std::filesystem::path 对象
    std::filesystem::path filepath("/path/to/file");

    // 获取 C 风格字符串的指针
    const char* cstr = filepath.string().c_str();

    // 使用 C 风格字符串
    std::cout << "C-style string: " << cstr << std::endl;

    return 0;
}
