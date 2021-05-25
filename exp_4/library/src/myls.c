#include "myls.h"
#include "mycp.h"
#include <string.h>

// 处理参数，返回ls要操作的路径，没有指定则默认返回当前路径，参数错误返回空
char *params_handler(int argc, char **argv) {
    if (argc > 2) {
        return NULL;
    }
    char *szPath = (char*)malloc(PATH_BYTES * sizeof(char));
    if (argc == 1) {
        // 说明没有指定目录，返回当前目录
        int nPathSize = PATH_BYTES;
        // 获取当前路径，最大500字节
        while (nPathSize < MAX_PATH_BYTES && getcwd(szPath, nPathSize) == NULL) {
            free(szPath);
            nPathSize += 10;
            szPath = (char*)malloc(nPathSize * sizeof(char));
        }
        if (nPathSize > MAX_PATH_BYTES) {
            return NULL;
        } else {
            return szPath;
        }
    } else if (argc > 2) {
        // 参数数量大于2，错误的参数
        return NULL;
    } else {
        // 表示参数数量为2，指定了目录
        strcpy(szPath, argv[1]);
        return szPath;
    }
}

// 执行ls和cp
void do_ls_cp(char *dirname) {
    // 因为下面会获取全路径，在DIR和filename之间添加了/，所以先去掉dirname最后的/
    int len = strlen(dirname);
    if (dirname[len - 1] == '/') {
        dirname[len - 1] = '\0';
    }
    DIR *dir_ptr = NULL;
    struct dirent *direntp = NULL;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1: cannot open %s\n",dirname);
    } else {
        // 读取目录下每一个文件和目录
        while((direntp = readdir(dir_ptr)) != NULL) {
            // 文件或目录名
            char *szFilename = direntp->d_name;
            // 过滤掉.和..
            if (strcmp(szFilename, ".") == 0 || strcmp(szFilename, "..") == 0) {
                continue;
            }
            // 然后获取全路径
            char fullPath[MAX_PATH_BYTES];
            sprintf(fullPath, "%s/%s", dirname, szFilename);
            // 文件或目录结构体
            struct stat currentstat = {};
            // 直接使用lstat打开，直接操作符号链接本身
            if (lstat(fullPath, &currentstat) == -1) {
                // 打开文件失败，跳过此文件
                printf("open file %s fail\n", szFilename);
                // free(fullPath);
                continue;
            }

            // 对每一个文件或者目录都要开启子进程，文件执行cp操作，目录执行递归操作，每个文件执行完之后子进程应该都要销毁
            pid_t pid = fork();
            if (pid == -1) {
                // 出错了
                printf("创建子进程失败！");
            } else if (pid == 0) {
                // 此处是子进程才会调用的

                // 获得子目录的全路径，+1是为了保证C字符串要以/0结尾
                // char *subPath = (char*)malloc(strlen(dirname) + strlen(szFilename) + 1);
                // sprintf(subPath, "%s/%s", dirname, szFilename);

                // 判断是否为目录
                if (S_ISDIR(currentstat.st_mode)) {
                    // 是目录，递归调用本函数，此处调用会导致进程链的产生，即fork里面又fork了
                    do_ls_cp(fullPath);
                } else {
                    // 不是目录，调用可执行程序mycp，命令行传递文件路径
                    // execl(dirname, "mycp", szFilename, "/home/xxx", (char *)0); // 本来应该是这样的
                    printf("fullpath = %s\n", fullPath);
                    cp(fullPath, "./cp_dir/"); // 直接变成了函数调用
                }
                // 子进程调用完之后，释放资源，返回父进程
                // free(fullPath);
                exit(0);
            } else {
                // 父进程，需要等待所有子进程完成后才能继续向下执行，使用的是阻塞模式，第三个参数设置为0则阻塞，设置为WNOHANG非阻塞
                waitpid(pid, NULL, 0);
                // free(fullPath);
            }
         }
        closedir(dir_ptr);
    }
}

