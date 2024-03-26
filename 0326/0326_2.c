#include <stdio.h>
#include <unistd.h>

int main(){
	if(access("b.txt", R_OK) == 0){
		printf("ok\n");
	}
	else{
		printf("No\n");
	}
}
