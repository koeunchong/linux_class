#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 64

void parent(int* []);
int child(int []);
void onerror(char *msg)
{
	printf("%s");
	exit(1);
}
int main()
{
	int p1[2], p2[2], p3[2];
	char msg[MSGSIZE];
	char *child1 = "I am a child1";
	char *child2 = "I am a child2";
	char *child3 = "I am a child3";
	int i;
	pid_t pid1, pid2, pid3;
	fd_set initset, newset;

	pid1 = pid2 = pid3 = 0;

	if(pipe(p1) == -1)
		onerror("fail to call pipe() #1\n");
	if(pipe(p2) == -1)
		onerror("fail to call pipe() #2\n"); 
	if(pipe(p3) == -1)
		onerror("fail to call pip() #3\n");
	if((pid1 = fork()) == -1)
		onerror("fail to call fork() #1\n");
	if(pid1 > 0)
		if((pid2 = fork()) == -1)
			onerror("fail to call fork() #2\n");
		else
			if((pid3 = fork()) == -1)
				onerror("fail to call fork() #3\n");

	if(pid1 > 0 && pid2 > 0 && pid3 > 0) { /* parent process */
		printf("parent: %d\n", getpid());
		close(p1[1]); close(p2[1]); close(p3[1]);

		FD_ZERO(&initset);
		FD_SET(p1[0], &initset);
		FD_SET(p2[0], &initset);
		FD_SET(p3[0], &initset);

		newset = initset;
		while(select(p3[0] + 1, &newset, NULL, NULL, NULL) > 0) {
			if(FD_ISSET(p1[0], &newset))
				if(read(p1[0], msg, MSGSIZE) > 0)
					printf("[parent] %s from child1\n", msg);
			if(FD_ISSET(p2[0], &newset))
				if(read(p2[0], msg, MSGSIZE) > 0)
					printf("[parent] %s from child2\n", msg);
			if(FD_ISSET(p3[0], &newset))
				if(read(p3[0], msg, MSGSIZE) > 0)
					printf("[parent] %s from child3\n", msg);
			newset = initset;
		}
	}
	else if(pid1 == 0 && pid2 == 0 && pid3 == 0) { /* first child */
		printf("child1: %d\n", getpid());
		close(p1[0]); close(p2[0]); close(p2[1]); close(p3[0]); close(p3[1]);

		for(i = 0; i < 3; i++) {
			sleep((i + 1) % 4);
			printf("child1: send message %d\n", i);
			write(p1[1], child1, MSGSIZE);
		}
		printf("child1: bye!\n");
		exit(0);
	}
	else if(pid1 > 0 && pid2 == 0 && pid3 == 0) { /* second child */
		printf("child2: %d\n", getpid());
		close(p1[0]); close(p1[1]); close(p2[0]); close(p3[0]); close(p3[1]);
		for(i = 0; i < 3; i++) {
			sleep((i + 3) % 4);
			printf("child2: send message %d\n", i);
			write(p2[1], child2, MSGSIZE);
		}
		printf("child2: bye!\n");
		exit(0);
	}
	else if(pid1 > 0 && pid2 > 0 && pid3 == 0) {
		printf("child3: %d\n", getpid());
		close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]); close(p3[0]);
		for(i = 0; i < 3; i++){
			sleep((i + 4));
			printf("child3: send message %d\n", i);
			write(p3[1], child3, MSGSIZE);
		}
		printf("child3: bye!\n");
		exit(0);
	}

}
