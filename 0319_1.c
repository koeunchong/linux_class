#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	int count = 0;
	char buf[1024];
	if((fd = (open(argv[1], O_RDONLY))) == -1){
		printf("error\n");
		exit(1);
	}
	ssize_t nread = read(fd, buf, sizeof(buf));
	for(int i = 0; i < strlen(buf); i++){
		if(buf[i] >= 65 && buf[i] <= 90 || buf[i] >= 97 && buf[i] <= 122){
			count++;
		}
	}
	printf("count : %d\n", count);
	close(fd);
}
