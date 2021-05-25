//
//

#ifndef C_VERSION_MYCP_H
#define C_VERSION_MYCP_H

#include <stdbool.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
#include <libgen.h>
//设置缓冲池大小
#define BUFFER_SIZE 4096
#define COPY_MODE 0644
#define ROW 100
#define COL 100
#define MAX_FILENAME 128
char *deal_path(char *file,char *file2);
void cp(char *file ,char * file2);
char* split(char*str,char delims[]);
#endif //C_VERSION_MYCP_H