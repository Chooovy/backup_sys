#include <iostream>
#include "compress.h"
#include "encrypt.h"
#include "tar.h"
#include "BackupManager.h"

int main()
{
    BackupManager bck("./char2four","./custom");
    bck.setTypeFilter(".cpp");
    bck.customBackup();
    return 0;
}