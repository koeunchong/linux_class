#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char** environ;

int main(){
	putenv("MYDATA=5");
	printf("%s\n", getenv("MYDATA"));
	execl("0507_3", "0507_3", environ, (char *)0); 
}
