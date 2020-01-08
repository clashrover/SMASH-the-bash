// Welcome to trash{ the bash

// basic functions{
	// o cd "dir" { changes the directory to "dir"
	// o pwd { prints the current directory
	// o mkdir "dir" { creates a directory called "dir"
	// o rmdir "dir" { removes the directory called "dir"
	// o exit { exits the shell 

#define str_len 100
#include <stdio.h>
#include <unistd.h>      //
#include <string.h>      // for tokenising
#include <sys/types.h>   // for mkdir
#include <sys/stat.h>    // for mkdir




void make_dir(char* str){
	int check = mkdir(str, 0777);
	if (check == -1){
		printf("%s\n","Error");
	}else{
		printf("%s\n", "Directory Created");
	}
}


int main(){
	char str[str_len];
	fgets(str, str_len, stdin);
	char* arr[3];
	int i =0;
	char *p = strtok(str," ");
	while(p != NULL) {
    	printf("%s\n", p);
    	arr[i++] = p;
    	p = strtok(NULL, " ");
	}
	// by now we have tokenised the string.
	// at max there could be only 3 strings seperated by " ";
	if(strcmp(arr[0],"cd")==0){
		// change_dir(arr[1]);
	}
	else if(strcmp(arr[0],"pwd")==0){
		// print_working_dir();
	}
	else if(strcmp(arr[0],"mkdir")==0){
		make_dir(arr[1]);
	}
	else if(strcmp(arr[0],"rmdir")==0){
		// remove_dir(arr[1]);
	}
	else if(strcmp(arr[0],"exit")==0){
		// exit();	
	}
	else{
		printf("%s\n", "sys command");
		// execute(arr[0]);
	}
	return 0;
}


