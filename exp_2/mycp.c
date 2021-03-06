#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define COPYMODE 0644
#define BUF 4096 

int main(int argc,char *argv[])
{
	//判断参数是否合格
	if(argc<3)
	{
		fprintf(stderr,"参数太少了\n");
		return -1;
	}
	int fd1,fd2;
	if((fd1=open(argv[1],O_RDONLY))<0)
	{
		perror("open");
		return -1;
	}
	/*拷贝到的目标文件如果没有就创建*/
	fd2 = open(argv[2],O_WRONLY | O_CREAT,0666);
	char buf[4096];
	int n;//定义n来接收实际读到的字节数
	while((n=read(fd1,buf,sizeof(buf)))>0)
	{
		write(fd2,buf,n);
	}
	close(fd1);
	close(fd2);
	printf("copy success\n");
	return 0;
}
