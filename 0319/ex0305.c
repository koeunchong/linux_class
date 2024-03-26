#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd;
	off_t newpos;

	if((fd = open(argv[1], O_RDONLY)) == -1){
			printf("error\n");
			exit(1);
		}

	newpos = lseek(fd, (off_t)0, SEEK_END);

	printf("file size : %ld\n", newpos);

	close(fd);
}
