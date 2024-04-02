#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	DIR *drip;
	if((dirp = opendir(argc[1])) == NULL){
			fprintf(stderr, "NOT FOUND\n");
			exit(1);
	}
	
	closedir(dirp);
}
