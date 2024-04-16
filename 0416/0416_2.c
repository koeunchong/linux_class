#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	int status;
	int x, y;
	
scan:
	printf("x : ");
	scanf("%d", &x);
	printf("y : ");
	scanf("%d", &y);
	
	if(!((x >= 1 && 10 >= x) && (y >= 1 && 10 >= y) && x < y)){
		printf("다시 입력 하세요\n");
		goto scan;
	}

	int mul = 1;
	int sum = 0;
	pid = fork();
	if(pid == 0){
		for(int i = x; i <= y ; i++){
			sum += i;
		}
		exit(sum);
	}
	else if(pid > 0){
		for(int i = 0; i < y; i++){
			mul *= x;
		}
		wait(&status);
		printf("sum + mul = %d\n", (mul + (status >> 8)));
		//printf("%d", *status >> 9);
	}
}
