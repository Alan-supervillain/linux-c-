#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
//#define 


int main(int argc,char* argv[])
{
	pid_t pid;
	int i;
	//char *buf="this is a daemon\n";
	pid=fork();
	if(pid<0){
	perror("fork失败:");
	exit(-1);
	}
	else if (pid>0){
	exit(0);
	}
	setsid();
	chdir("/");
	umask(0);
	for(i=0;i<getdtablesize();i++){
	close(i);
	}
	if(0!=system("sudo")){
	perror("没有sudo权限");
	exit(-1);
	}
	system("one-key-online.sh >> ./daemon.log");
	return 0;
}
