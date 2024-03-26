#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	if(int fd = open("data.txt", O_RDWR | O_CREAT) == -1){
		printf("failed!\n");
		exit(0);
	}
	printf("%d\n", fd);
	close(fd);
	return 0;
}
