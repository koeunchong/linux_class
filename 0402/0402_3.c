#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char name[1024];
	int nread;

	if(argc != 2)
		exit(1);

	nread = readlink(argv[1], name, 1024);

	printf("%s is %s a soft-link\n", name, );
	
}
