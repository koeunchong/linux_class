#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int gNum;

int main() {
    pid_t pid;
    pid = fork();
    
    if (pid > 0) {
        while (1) {
            printf("Parent_forkpid : getpid(%d), getppid(%d), gNum(%d)\n", (int)getpid(), (int)getppid(), gNum);
            sleep(5);
            gNum++;
        }
    } else if (pid == 0) {
        while (1) {   
			pid_t gpid = getpid();
			pid_t gppid = getppid();
            printf("Child_forkpid : getpid(%d), getppid(%d), gNum(%d)\n", (int)getpid(), (int)getppid(), gNum);
            sleep(5);
            gNum++;
        }
    }
}

