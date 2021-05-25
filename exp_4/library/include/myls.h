#ifndef LS_L_C_H
#define LS_L_C_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#define PATH_BYTES 50 // 文件路径名默认字节数
#define MAX_PATH_BYTES 500 // 文件路径名最大字节数
#define MAX_FILE_COUNT 100 // 目录下最大文件数
// 处理参数
char *params_handler(int argc, char **argv);
// 执行ls和cp
void do_ls_cp(char*);
#endif
