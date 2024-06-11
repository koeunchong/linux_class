#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 100

int main(){
	int filedes;

	printf("[exec] standartd output\n");
	sleep(1);

	filedes = open("./fifo", O_WRONLY);
	write(filedes, "from exec via FIFO", MSGSIZE);
	close(filedes);
}
