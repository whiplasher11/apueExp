//
// Created by 85192 on 2020/4/4.
//
//    cp("/home/hjc/lab4/readme.md","/home/hjc/");
#include "myls.h"


int main(int argc,char **argv) {
    char *dirname = params_handler(argc, argv);
    do_ls_cp(dirname);
    free(dirname);
    return 0;
}