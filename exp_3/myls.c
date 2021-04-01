#include <stdio.h>
#include <stdlib.h>  
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

 #define PATH "./" 

void print_filename(struct dirent *dname){
        printf("%s \n",dname->d_name);
}
void print_grname(__gid_t gname){
        struct group *g = NULL;//定义getgrgid结构体指针gr_gid,并初始化为空
        g = getgrgid(gname);//gr_gid指针绑定函数getgrgid(st.st_gid)，st.st_gid是stat结构体对象st的成员变量
        if (NULL == g)//判断gr_gid指针是否指向成功
        {
                perror("getgrgid");
                exit(0);
        }
        char *g_gid = g->gr_name;//定义char*型指针g_gid用来保存得到的组名
        printf("%s  ",g_gid);

}

void print_time(struct stat st){
        struct tm *local_time = NULL;//定义localtime结构体指针local_time，并初始化为空
        local_time = localtime(&st.st_ctime);
        if(local_time == NULL){
                perror("localtime");
                exit(0);
        }
        int n_num = local_time->tm_mon;//定义int型变量n_num用来保存local_time指针访问到的月份，注意：这里得到的月份是数字表示，且localtime函数得到的月份是0~11,不符合正常思维的1~12
        char *n_mon;//定义char*型变来嗯n_mon，用来转换数字月份到英文简写月份
        int n_day = local_time->tm_mday;//定义int型变来嗯n_day用来存放local_time指针访问到的日期
        int n_hour = local_time->tm_hour;//定义int型变来嗯n_hour用来存放local_time指针访问到的小时
        int n_min = local_time->tm_min;//定义int型变来嗯n_min用来存放local_time指针访问到的分钟
        switch (n_num)//利用switch-case语句用来转换数字月份到英文简写月份
        {
        case 0:
                n_mon = "Jan";
                break;
        case 1:
                n_mon = "Feb";
                break;
        case 2:
                n_mon = "Mar";
                break;
        case 3:
                n_mon = "Apr";
                break;
        case 4:
                n_mon = "May";
                break;
        case 5:
                n_mon = "Jun";
                break;
        case 6:
                n_mon = "Jul";
                break;
        case 7:
                n_mon = "Aug";
                break;
        case 8:
                n_mon = "Sep";
                break;
        case 9:
                n_mon = "Otc";
                break;
        case 10:
                n_mon = "Nov";
                break;
        case 11:
                n_mon = "Dec";
                break;
        default:
                break;
        }

        printf("%s%d %d:%d  ",n_mon,n_day,n_hour,n_min);

}
void print_type(struct stat st){
        char type_dir;
        if(S_ISREG(st.st_mode)) type_dir='-';
        else if(S_ISDIR(st.st_mode)) type_dir='d';
        else if(S_ISCHR(st.st_mode)) type_dir='c';
        else if(S_ISBLK(st.st_mode)) type_dir='b';
        else if(S_ISSOCK(st.st_mode)) type_dir='s';
        else if(S_ISLNK(st.st_mode)) type_dir='l';
        else type_dir='?';

        printf("%c",type_dir);
}

void print_perm(__mode_t mode){
        int n_size,n_link;

        char n_power[10] = {};//定义一个固定长度的char型数组n_power用来存放九个权限位
        int POS[10]={S_IRUSR,S_IWUSR,S_IXUSR,S_IRGRP,S_IWGRP,S_IXGRP,S_IROTH,S_IWOTH,S_IXOTH};

        for(int i=0;i<9;i+=3){
               n_power[i] = (POS[i]&mode)?'r':'-';
        }
        for(int i=1;i<9;i+=3){
                n_power[i] = (POS[i]&mode)?'w':'-';
        }        
        for(int i=2;i<9;i+=3){
                n_power[i] = (POS[i]&mode)?'x':'-';
        }

        printf("%s ",n_power);
}

void print_link(__nlink_t link){
        printf("%ld   ",link);
}

void print_username(__uid_t uid){

        struct passwd *u_uid = NULL;//定义getpwuid结构体指针u_uid，并初始化为空
        u_uid = getpwuid(uid);//u_uid指针绑定函数getpwuid(st.st_uid)，st_st_uid是stat结构体对象st的成员变量
        if (u_uid == NULL)//判断u_uid指针是否指向成功
        {
                perror("getpwuid Failed");
                exit(0);
        }
        char *g_uid = u_uid->pw_name;//定义char*型指针g_uid用来保存得到的用户名
        printf("%s ",g_uid);
}


int main (int argc,char **argv){

        DIR *p_dir=NULL;
        char *path = PATH;
        if(argc>2){
                path=argv[1];
        }
        p_dir=opendir(path);
        if(p_dir == NULL){
                perror("openDir failed");
                exit(0);
        }


        char *pname;
        struct dirent *d_dir = NULL;
        struct stat currentstat;
        memset(&currentstat,0,sizeof(currentstat));//清空这块内存
        int flag = 1;
        if(argc>2&&argv[2][0]=='y') flag=0;
        else flag=1;
        while(d_dir = readdir(p_dir)){
                if('.'==d_dir->d_name[0]&&flag) continue;
                pname=d_dir->d_name;
                if(stat(pname,&currentstat)<0){
                        perror("stat error");
                        continue;
                }
                print_type(currentstat);
                print_perm(currentstat.st_mode);
                print_link(currentstat.st_nlink);
                print_username(currentstat.st_uid);
                print_grname(currentstat.st_gid);
                printf("%ld ",currentstat.st_size);
                print_time(currentstat);
                print_filename(d_dir);

        }


        
}
