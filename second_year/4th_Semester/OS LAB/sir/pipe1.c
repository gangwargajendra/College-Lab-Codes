#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#define MSGSIZE 12 
  
int main() { 
    char inbuf[MSGSIZE]; 
    int p[2], pid, nbytes; 
    char msg1[] = "Hello IIITG"; 
    //pipe() creates a pipe for communication between two processes. It returns negative if creation is unsuccessful   
    if (pipe(p) < 0) 
        exit(1); 
  
    //pipe takes an array of 2 integer as input and assigns identifer  values   corresponding to the two end of pipe
    if ((pid = fork()) > 0) { //parent process
        close(p[0]);        
        write(p[1], msg1, MSGSIZE); //p[1] end of the pipe is for writing a message to be passed
        close(p[1]);
        wait(NULL); //wait for child
    }else { //child process
        close(p[1]);
		read(p[0], inbuf, MSGSIZE); //p[0] is for the read end of the pipe
        printf("%s\n", inbuf); 
        close(p[0]);	 
        printf("Finished reading\n"); 
    } 
    return 0; 
} 