#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork();//value of pid will be 0 in child process and positive int in parent process
    if (pid < 0) { /* error occurred */
        printf("Fork Failed");
        return 1;
    }else if (pid == 0) { /* child process */
        execlp("./test1","test1","Hello",NULL); // execlp replaces the child process with the new program
        // if new prcoess is successfully replaced, then the child process will not execute the next statement
        printf("In child process");
    }else { /* parent process */
        /* parent will wait for the child */
        wait (NULL);
        printf ("\nChild Complete\n");
    }
    return 0;
}