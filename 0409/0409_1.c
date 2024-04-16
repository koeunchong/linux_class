#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main(){
	unsigned int num;
	int sum = 0;
	printf("num : ");
	scanf("%d", &num);
	pid_t pid = fork();
	if(pid > 0){
		for(int i = 0; i <= num; i++){
			sum += i;
		}
		printf("덧셈 : %d\n", sum);
	}
	else if(pid == 0){
		sum = 1;
		for(int i = 1; i <= num; i++){
			sum *= i;
		}
		printf("곱셋 : %d\n", sum);
	}
	return 0;
}
	
