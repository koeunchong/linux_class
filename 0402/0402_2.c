#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{ 
	DIR *dirp; 
	struct dirent *dentry;
	int file_count = 0, dir_count = 0;
	DIR *dirp2;

	if((dirp = opendir(argv[1])) == NULL) 

	exit(1);

	while(dentry = readdir(dirp)) {
		if(dentry->d_ino != 0) {
			printf("%s\n", dentry->d_name); 
			if((dirp2 = opendir(dentry->d_name)) == NULL){
				file_count++;
			}
			else
			{
				closedir(dirp2);
				dir_count++;
			}
		}
	} 

	printf("file : %d, dir : %d\n", file_count, dir_count);

	closedir(dirp); 
} 
