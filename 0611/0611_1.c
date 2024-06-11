#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


int main()
{
	pid_t pid;
	int fd[2];
	int sum;
	char c1[10];
	char c2[10];
	if(pipe(fd) == -1){
		printf("fail to call pipe\n");
		exit(1);
	}
	if((pid = fork()) == -1)
	{
		printf("fail to fork");
		exit(1);
	}
	else if(pid > 0){
		close(fd[0]);
		scanf("%s %s", c1, c2);
		write(fd[1], c1, 10);
		write(fd[1], c2, 10);
		printf("[parent] bye!\n");
	}
	else
	{
		close(fd[1]);
		read(fd[0], c1, 10);
		read(fd[0], c2, 10);
		sum = atoi(c1) + atoi(c2);
		printf("[child]sum = %d\n", sum);
		printf("[child] bye!\n");
	}
}

