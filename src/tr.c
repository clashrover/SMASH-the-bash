// Welcome to SMASH: the bash

// basic functions{
	// o cd "dir" : changes the directory to "dir"
	// o pwd : prints the current directory
	// o mkdir "dir" : creates a directory called "dir"
	// o rmdir "dir" : removes the directory called "dir"
	// o exit : exits the shell 

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



void make_dir(const char* str){
	int check = mkdir(str, 0777);
	if (check ==0) {
		printf("%s : %s\n", str,"Directory Created");
		return;
	}
	printf("%s\n", "failed");
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
   		return check;
   }
   return check;
}

void change_dir(const char* path){
	int check  = chdir(path);
	if(check==0){
		printf("%s%s\n", "Directory changed to: ", path);
	}else{
		printf("%s\n", "failed");
	}
}

void print_working_dir(){
	char cwd[str_len];
	size_t path_len = str_len; 
	if(getcwd(cwd,path_len)!=NULL){
		printf("Current Directory is: %s", cwd);
	}else{
		printf("%s\n", "failed");
	}
}

int exe_files(char** arr){
	// don't keep any command except print after execvp because it will run only if execvp returns.
	// The exec() family of functions replaces the current process image with a new process image.
	// I have used file descriptors. fd0 is stdin fd1 is stdout, fd2 is stderr
	if (fork()==0){
		if(arr[1]!=NULL){
			if(strcmp(arr[1],">")==0){
				close(1);
				open(arr[2],O_WRONLY |O_CREAT, 0666);  //0666 determine access permisions
			}
			if(strcmp(arr[1],"<")==0){
				close(0); //releases fd0
				open(arr[2],O_RDONLY); //read only 
			}
			if(arr[3]!=NULL){
				if(strcmp(arr[1],"<")==0 && strcmp(arr[3],">")==0){
					close(0);
					open(arr[2],O_RDONLY);
					close(1);
					open(arr[4],O_WRONLY |O_CREAT, 0666);
				}
			}
		}
		if(execvp(arr[0],arr)<0){
			perror("execvp() in exe_files");
		}
		exit(1);
	}else{
		wait(NULL);
	}

}

void pipeline(char** arr,int size){
	//remember the child inherits open file descriptors
	char* arg[1000];
	char* dest[1];
	int k=0;
	int x=0;
	for(int i=0;i<size;i++){
		if(strcmp(arr[i],"|")==0){
			continue;
		}
		if(strcmp(arr[i],">")==0){
			x=1;
			dest[0] = arr[i+1];
			break;
		}
		arg[k]=arr[i];
		k++;
	}
	arg[k]=NULL;
	int i=0;
	int n_files = k;
	int num_pipes=k-1;

	int p[2*num_pipes];
	int child_status;
	pid_t tpid;
	while(i<n_files){
		if(i<n_files-1){
			pipe(p+2*i);
		}
		pid_t child_pid;
		child_pid = fork();
		if(child_pid<0){
			perror("fork in pipeline");
			return;
		}
		if(child_pid==0){
			if(i>0){
				dup2(p[2*(i-1)],0);
				close(p[2*(i-1)]);
				close(p[(2*i)-1]);
			}
			if(i<n_files-1){
				close(p[2*i]);
				dup2(p[(2*i)+1],1);
				close(p[2*i+1]);
			}
			if(i==n_files-1 && x==1){
				close(1);
				if(open(dest[0],O_WRONLY |O_CREAT, 0666)<0){
					perror("open");
				}  //0666 determine access permisions
				execvp(arg[i],arg);
				exit(0);
			}
			execvp(arg[i],arg);
			perror("execvp in pipe");
			exit(0);
		}else{
			if(i>0){
				close(p[2*(i-1)]);
				close(p[(2*i)-1]);
			}
			i++;
			wait(NULL);
		}
	}

}



int main(){
	system("clear"); 
	system("clear"); 
	printf("%s\n", "--------------------------WELCOME TO SMASH: THE BASH--------------------------");
	//int p_id = fork();  // create a child process, both child and parent process terminate when we type "exit";
						// the parent is given wait() command, thus it will be invoked only when child process exits.
	//if(p_id==0){
		//printf("%s\n", "hi from child");
		printf("%s: ", "$>");
		char str[str_len]; 
   		fgets(str, str_len, stdin);		//take input string first time
   		str[strlen(str)-1]=0;		//fgets() also take a trailing \n character. Solution to that, put null character at the end
   		while(strcmp(str,"exit")!=0){
			char* arr[1000];
			int i =0;
			char *p = strtok(str," ");
			while(p != NULL) {
		    	arr[i++] = p;
		    	p = strtok(NULL, " ");
			}
			int size=i;
			// by now we have tokenised the string.
			// at max there could be only 3 tokens seperated by " ";
			if(strcmp(arr[0],"help")==0){
				printf("%s\n", "----------HELP---------");
				printf("%s\n", "-----Basic Functions-----");
				printf("%s\n", "o cd [dir] : changes the current directory to 'dir'");
				printf("%s\n", "o pwd : prints the current directory");
				printf("%s\n", "o mkdir [dir] : creates a directory named 'dir'");
				printf("%s\n", "o rmdir [dir] : removes the non-empty/empty directory name 'dir'");
				printf("%s\n", "o file1 | file2 pipes output of file1 to file2");
				printf("%s\n", "o filed1 < inp.txt > outp.txt : executes file1 with input from inp.txt and outputs it to out.txt");
				printf("%s\n", "o filed1 | file2 | file3 .... > out.txt : outputs piped output to out.txt");
			}
			else if(strcmp(arr[0],"cd")==0){
				change_dir(arr[1]);
			}
			else if(strcmp(arr[0],"pwd")==0){
				print_working_dir(); printf("\n");

			}
			else if(strcmp(arr[0],"mkdir")==0){
				make_dir(arr[1]);
			}
			else if(strcmp(arr[0],"rmdir")==0){
				int r=remove_dir(arr[1]);
				if (r==-1){ printf("%s\n", "failed"); }
			}
			else if(strcmp(arr[1], "|")==0){
				pipeline(arr,size);
			}
			else{
				arr[size]=NULL;
				exe_files(arr);
			}
   			printf("%s: ", "$>");
   			fgets(str, str_len, stdin);     // again take the input as "exit" not typed yet
   			str[strlen(str)-1]=0;
   		} 
	system("clear");
	system("clear"); 
	return 0;
}