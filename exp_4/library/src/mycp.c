#include "mycp.h"


void cp(char * file,char * file2){
    int in_fd, out_fd, n_chars;
    char buf[BUFFER_SIZE];
    struct stat filebuf1;
    struct stat filebuf2;
    char *filename=NULL;


    //源文件为文件夹
    stat(file,&filebuf1);
    if(S_ISDIR(filebuf1.st_mode)) {
        printf(file);
        printf("为文件目录跳过\n");
        return ;
    }
    //判断目标是否是文件夹
    stat(file2,&filebuf2);
    if(S_ISDIR(filebuf2.st_mode))
        filename = deal_path(file,file2);
    else
        filename = file2;
    file2 = filename;

    in_fd=open(file,O_RDONLY);

    while((n_chars = read(in_fd, buf, BUFFER_SIZE))>0)
    {
        if(-1 == (out_fd = creat(file2, COPY_MODE)) )
        {
            printf(file2);
            printf("文件打开失败\n");
            return ;
        }

        if(write(out_fd, buf, n_chars) != n_chars)
        {
            printf(file2);
            printf("文件写入失败\n");
            return ;
        }
        
    }
    printf(file2);
    printf("复制完成\n");
    close(in_fd);
    close(out_fd);
}

//获得被复制文件全路径
char *deal_path(char *file,char *file2)
{
    char *path;
    path = malloc( MAX_FILENAME);
    char * filename = split(file,"/");


    strcat(path,file2);
    if(file2[strlen(file2)-1] == '/'){
            strcat(path,filename);
    }else{
        strcat(path,"/");
        strcat(path,filename);
    }

    return path;
}
//分割
char* split(char *str,char delims[]) {
    char buf[MAX_FILENAME]={0};
    int i=0;
    while(*str != '\0')
    {
        buf[i] = *str;
        i++;
        str++;
    }

    char *result = NULL;
    char *pre = NULL;
    result = strtok(buf, delims);
    while (result != NULL) {
        pre = result;
        result = strtok(NULL, delims);
    }
    return pre;
}




void test(){
    printf("hello");
}