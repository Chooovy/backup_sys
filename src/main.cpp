#include "do.h"
#include <iostream>

int main() {
    std::string in = "/home/marcus/backup_sys/tar_in";
    std::string out = "/home/marcus/backup_sys/temp/tmp";
    Do testdo(in, out);
    // testdo.Backup("123");
    testdo.Restore("123");
    return 0;
}