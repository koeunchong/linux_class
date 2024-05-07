#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv){
	pid_t pid;
	pid = fork();
	int fd;

	if(argc <= 1){
		printf("인자값을 넣으시오\n");
		exit(1);
	}

	if((pid) > 0)
	{
		sleep(1);
		exit(1);
	}
	else if(pid == 0)
	{
		setsid();
		
		fd = open(argv[1], O_WRONLY | O_CREAT);
		if(fd < 0){
			printf("error");
			exit(1);
		}
		while(1){
			time_t t = time(NULL);
			//printf("현재 시간 : %s\n", ctime(&t));
			char *buf = ctime(&t);
			write(fd, buf, strlen(buf));
			sleep(10);
		}
	}
}
