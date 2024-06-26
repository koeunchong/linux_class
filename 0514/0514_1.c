#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void int_handle(int);

int num = 0;

int main(){
	static struct sigaction act;

	void int_handle(int);

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	while(1)
	{
		printf("I'm sleepy..\n");
		sleep(1);
		if(num >= 1){
			exit(0);
		}
	}
}

void int_handle(int signum){
	printf("SIGINT:%d\n", signum);
	printf("int_handle called %d times\n", ++num);
	int fd = open("a.txt", O_WRONLY | O_CREAT, 644);
	if(fd == -1) 
	{
		printf("file open error\n");
		exit(1);
	}
	char buf[] = "Goodbye!\n";
	write(fd, buf, strlen(buf));
	close(fd);
}
