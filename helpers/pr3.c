// Program to demonstrate bottom to up execution 
// of processes using fork() and wait() 
#include <stdio.h> 
#include <sys/wait.h> // for wait() 
#include <unistd.h> // for fork() 
int main() 
{ 
    // creating 4 process using 2 fork calls 
    // 1 parent : 2 child : 1 grand-child 
    pid_t id1 = fork(); 
  
    // parent process 
    if (id1 > 0){ //&& id2 > 0) { 
        wait(NULL); 
        wait(NULL); 
        printf("%s\n", "Parent Terminated");
    } 
  
    // 1st child 
    else if (id1 == 0){ //&& id2 > 0) { 
  
        // sleep the process for 2 seconds 
        // to ensure 2nd child executes first 
        sleep(2); 
        //wait(NULL); 
        printf("%s\n", "1st child Terminated");
    } 
  
    // // second child 
    // else if (id1 > 0 && id2 == 0) { 
    //     // sleep the process for 1 second 
    //     sleep(1); 
    //     printf("%s\n", "2nd Child Terminated");
    // } 
  
    // // grand child 
    // else { 
    //     printf("%s\n","Grand Child Terminated"  );
    // } 
  
    return 0; 
} 

    // char str[str_len];
    // fgets(str, str_len, stdin);
    // char* arr[3];
    // int i =0;
    // char *temp = strtok(str,"\n");
    // char *p = strtok(temp," ");
    // while(p != NULL) {
 //     //printf("%s\n", prompt for User Input in cp);
 //     arr[i++] = p;
 //     p = strtok(NULL, " ");
    // }
    // // by now we have tokenised the string.
    // // at max there could be only 3 tokens seperated by " ";
    // int r=-1;
    // if(strcmp(arr[0],"cd")==0){
    //  r=change_dir(arr[1]);
    // }
    // else if(strcmp(arr[0],"pwd")==0){
    //  // print_working_dir();
    // }
    // else if(strcmp(arr[0],"mkdir")==0){
    //  r=make_dir(arr[1]);
    // }
    // else if(strcmp(arr[0],"rmdir")==0){
    //  r=remove_dir(arr[1]);
    // }
    // else if(strcmp(arr[0],"exit")==0){
    //  // exit();  
    // }
    // else{
    //  printf("%s\n", "sys command");
    //  // execute(arr[0]);
    // }

    // if (!r){
    //  printf("%s\n", "Successful");
    // }else{
    //  printf("%s\n", "Error");
    // }