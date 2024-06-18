#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void onerror(char *msg){
	printf("%s");
	exit(1);
}
int mul, sum;

int main()
{
	pid_t pid;
	int p1[2], p2[2];
	char c1[10];
	char c2[10];
	if(pipe(p1) == -1)
		onerror("fail to call pipe1\n")
	if(pipe(p2) == -1)
		onerror("fail to call pipe2\n");
	if((pid = fork()) == -1)
		onerror("fail to fork");
	else if(pid > 0){
		if((pid2 = for()) == -1)
			onerror("fail to call fork() 2\n");
		if(pid2 > 0){
			close(p2[0]);
			close(p1[0]);
			scanf("%s %s", c1, c2);
			write(p1[1], c1, 10);
			write(p1[1], c2, 10);
			write(p2[1], c1, 10);
			write(p2[1], c2, 10);
			printf("[parent] bye!\n");
		}
		else if(pid2 == 0){
			close(p2[1]);
			read(p2[0], c1, 10);
			read(p2[0], c2, 10);
			mul = atoi(c1) * atoi(c2);
	}
	else
	{
		close(p1[1]);
		read(p1[0], c1, 10);
		read(p1[0], c2, 10);
		sum = atoi(c1) + atoi(c2);
	}
}

