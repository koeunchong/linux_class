#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	printf("getpgrp():%d\n", getpgrp());
	printf("getpgrp():%d\n", getpgrp());
	printf("getpgid(getpid()):%d\n", getpgid(getpid()));
	printf("getsid():%d\n", getsid(getpid()));
}

