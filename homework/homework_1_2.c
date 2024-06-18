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
    int fd = open("log.txt", O_RDWR | O_APPEND | O_CREAT, 0644);
    if(fd < 0){
        perror("file open Error");
        exit(1);
    }

    time_t now;
    time(&now);

    char *reason;
    if(WIFEXITED(status)){
        reason = "exit";
    } else {
        reason = "Signal(bye~)";
    }
	printf("bye~\n");
    char log[256];
    int len = snprintf(log, sizeof(log), "%d\t%d\t%s\t%s\n", getpid(), count, ctime(&now), reason);
    
    write(fd, log, len);
    close(fd);
	exit(0);
}

int main(){
    sigset_t set;
    struct sigaction act;

    act.sa_handler = handler;
    sigfillset(&(act.sa_mask));
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    while (count < 3) { // 3번 반복을 위해 설정 (3분 동안 반복을 원한다면 다른 조건 설정 필요)
        sigprocmask(SIG_BLOCK, &set, NULL);

        pid_t pid = fork();

        if(pid == 0) {
            for(int i = 0; i < 10; i++){
                sleep(1);
                printf("I am a child\n");
                fflush(stdout);

                if(i == 5){
                    sigprocmask(SIG_UNBLOCK, &set, NULL);
					printf("unblock\n");
                }
            }
            exit(10);
        } else if(pid > 0) {
            wait(&status);
            count++;
        } else {
            perror("fork error\n");
            exit(1);
        }
    }

    return 0;
}

