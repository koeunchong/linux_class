#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *fd;
	int count = 0;
	char buf[1024];
	fd = fopen(argv[1], "r");
	if(fd == -1){
		printf("error\n");
		exit(1);
	}
	ssize_t nread = fread(buf, sizeof(buf), 1, fd);
	for(int i = 0; i < strlen(buf); i++){
		if(buf[i] >= 65 && buf[i] <= 90 || buf[i] >= 97 && buf[i] <= 122){
			count++;
		}
	}
	printf("count : %d\n", count);
	fclose(fd);
}
