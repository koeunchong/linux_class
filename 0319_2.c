#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	int count = 0;
	char buf[1024];
	ssize_t nwrite;
	off_t newpos;
	if((fd = (open(argv[1], O_RDWR))) == -1){
		printf("error\n");
		exit(1);
	}
	ssize_t nread = read(fd, buf, sizeof(buf));
	for(int i = 0; i < nread; i++){
		if(buf[i] >= 97 && buf[i] <= 122){
			buf[i] = buf[i] - 'a' + 'A';
		}
	}
	newpos = lseek(fd, (off_t)0, SEEK_SET);
	if((nwrite = write(fd, buf, nread)) < 0){
		printf("erorr\n");
		exit(1);
	}
	printf("%s", buf);
	close(fd);
}
