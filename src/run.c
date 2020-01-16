#define str_len 100
#include <stdio.h>
// fprintf()
// printf()
// stderr
// getchar()
// perror()
#include <unistd.h>
//chdir()
// fork()
// exec()
// pid_t
#include <string.h>      // for tokenising
// strcmp()
// strtok()
#include <sys/types.h>   // for mkdir
#include <dirent.h>
#include <stdlib.h>
// malloc()
// realloc()
// free()
// exit()
// execvp()
// EXIT_SUCCESS, EXIT_FAILURE
#include <sys/wait.h> // for wait() 
#include <sys/stat.h> //for open
#include <fcntl.h>	//for open
int main(){
	char* arr[2];
	char str[] = "./exe/main";
	arr[0]=str;
	arr[1]=NULL;	
	if(fork()==0){
		if(execvp(arr[0],arr)<0){
			perror("execvp run");
		}
	}else{
		wait(NULL);
	}
	return 0;
}