#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	pid_t pid;
	int seconds = 0;

	if((pid = fork()) > 0){
		sleep(2);
		printf("bye(parents)");
	}
	else if(pid == 0){
		pid_t ppid = getppid();
		kill(ppid, SIGINT);
		printf("bye(child)");
		exit(0);
	}
	else
		printf("fail to fork\n");
}
