/*#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
	pid_t pid[3];
	int i = 0;
	for(i = 0; i < argc - 1; i++){
		pid[i] = fork();
	}
	char *arg[] = {"wc", "-lwc", argv[i + 1], (char *)0};
	if(pid > 0){
		sleep(1);
	}
	else if(pid == 0){
		execv("/bin/wc", arg);
		printf("failed ex\n");
	}
	printf("finish\n");
	return 0;
}*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    pid_t pid[argc - 1]; // argc는 프로그램의 실행 인자 개수이므로, fork할 자식 프로세스 수는 argc - 1입니다.

    int i;
    for(i = 0; i < argc - 1; i++){
        pid[i] = fork();
        if(pid[i] == -1){
            perror("fork");
            return 1;
        }
        else if(pid[i] == 0){ // 자식 프로세스의 경우
            char *arg[] = {"wc", "-lwc", argv[i + 1], NULL}; // 실행 인자 배열 생성
            execv("/usr/bin/wc", arg); // wc 프로그램 실행
            perror("execv"); // execv가 실패한 경우에만 실행됩니다.
            return 1;
        }
    }

    // 부모 프로세스의 경우
    for(i = 0; i < argc - 1; i++){
        wait(NULL); // 자식 프로세스들의 종료를 기다립니다.
    }

    printf("finish\n");
    return 0;
}

