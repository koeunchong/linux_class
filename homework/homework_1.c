#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int count = 0;
int status;

void handler(int signum){
	int fd = open("log.txt", O_RDWR | O_APPEND);
	char *reason;
	if(fd < 0){
		printf("file open Error");
		exit(0);
	}
	time_t now;
	time(&now);
	
	if(WIFEXITED(status)){
		reason = "exit";
	}
	else{
		reason = "Signal(bye~)";
	}
	
	printf("%d\t%d\t%s\t%s", getpid(), count, ctime(&now), reason);
}

int main(){
	sigset_t set;
	static struct sigaction act;

	act.sa_handler = handler;
	sigfillset(&(act.sa_mask));
	sigaction(SIGCHLD, &act, NULL);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, NULL);
	
	pid_t pid = fork();

	if(pid == 0)
	{
		for(int i = 0; i < 10; i++){
			sleep(1);
			printf("I am a child");
			
			if(i == 5){
				sigprocmask(SIG_UNBLOCK, &set, NULL);
			}
		}
		exit(10);
	}
	else if(pid > 0){
		wait(&status);
		count++;
	}
	else{
		printf("fork error\n");
		exit(0);
	}

}
