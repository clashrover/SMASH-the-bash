#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h>
#include<string.h>

int main(){
	int p_id = fork();
	if(p_id==0){
		//printf("%s\n", "hi from child");
		char str[20]; 
		printf("%s :", "$>");
   		fgets(str, 20, stdin);
   		str[strlen(str)-1]=0;
   		while(strcmp(str,"exit")!=0){
   			printf("%s :", "$>");
   			fgets(str, 20, stdin);
   			str[strlen(str)-1]=0;
   		} 
   		exit(1);
	}else{
		//printf("%s\n", "parent goes on hold");
		wait(NULL);
		//printf("%s\n", "parent back on");
	}
}