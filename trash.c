// Welcome to trash: the bash

// basic functions{
	// o cd "dir" : changes the directory to "dir"
	// o pwd : prints the current directory
	// o mkdir "dir" : creates a directory called "dir"
	// o rmdir "dir" : removes the directory called "dir"
	// o exit : exits the shell 

#define str_len 100
#include <stdio.h>
#include <unistd.h>      //
#include <string.h>      // for tokenising
#include <sys/types.h>   // for mkdir
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>


int make_dir(const char* str){
	int check = mkdir(str, 0777);
	if (check ==0) {
		printf("%s : %s\n", str,"Directory Created");
	}
	return check;
}


int remove_dir(const char *path){
   DIR *dir = opendir(path);         //we enter a directory
   size_t path_len = strlen(path);   //is used to represent the size of objects in bytes
   int chk_if_dir_emp = -1;          //this will donote if directory is empty and ready to delete
   if (!dir){						// if directory was able to be opened then error
   	return -1;
   }
   else{
      struct dirent *p;				//struct in c is a group of variables that can be accessed by single pointer
      								//here we are using struct that is dirent, we creater a pointer p of this type
      chk_if_dir_emp = 0;			//even if the directory is non empty we would have to check it, so consider that directory is non empty now
      while ((p=readdir(dir))){    // readdir() returns a pointer to dirent structure representing the next directory in the directory stream
      													// it would return NULL on reaching the end of directory or if some other error
          int chk_if_dir_emp2 = -1;						// as p was not null there are other files/directory in this directory
          												// hence value of chk_if_dir_emp can change, so we will use another variable
          char *buf;									// buf will be the complete path to the file
          size_t len;							
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")){  //Leave out "." i.e "current_directory" and ".." "previous directory" as we don't want to recurse on them.
             continue;
          }
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);
          if (buf){
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);			//we concated path, p.d_name into buf 
             if (!stat(buf, &statbuf)){
                if (S_ISDIR(statbuf.st_mode)){						// to check if file that buf contains the address is a directory or not
                   chk_if_dir_emp2 = remove_dir(buf);				// recurse if directory
                }
                else{
                   chk_if_dir_emp2 = unlink(buf);					//else unlink the regular file
                }
             }
             free(buf);												// free the memory
          }
          chk_if_dir_emp = chk_if_dir_emp2;							//assign the value
      }
      closedir(dir);												//close the directory as it is empty now
   }
   int check=-1;
   if (chk_if_dir_emp==0){
      check = rmdir(path);								//remove the empty directory using rmdir
   }
   return check;
}

int change_dir(const char* path){
	int check  = chdir(path);
	if(check==0){
		printf("%s%s\n", "Directory changed to: ", path);
	}
	return check;
}


int main(){
	char str[str_len];
	fgets(str, str_len, stdin);
	char* arr[3];
	int i =0;
	char *temp = strtok(str,"\n");
	char *p = strtok(temp," ");
	while(p != NULL) {
    	//printf("%s\n", p);
    	arr[i++] = p;
    	p = strtok(NULL, " ");
	}
	// by now we have tokenised the string.
	// at max there could be only 3 tokens seperated by " ";
	int r=-1;
	if(strcmp(arr[0],"cd")==0){
		r=change_dir(arr[1]);
	}
	else if(strcmp(arr[0],"pwd")==0){
		// print_working_dir();
	}
	else if(strcmp(arr[0],"mkdir")==0){
		r=make_dir(arr[1]);
	}
	else if(strcmp(arr[0],"rmdir")==0){
		r=remove_dir(arr[1]);
	}
	else if(strcmp(arr[0],"exit")==0){
		// exit();	
	}
	else{
		printf("%s\n", "sys command");
		// execute(arr[0]);
	}

	if (!r){
		printf("%s\n", "Successful");
	}else{
		printf("%s\n", "Error");
	}
	return 0;
}


