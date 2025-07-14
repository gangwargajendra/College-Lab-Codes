#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    fork();
    printf("Current:%d parent: %d\n",getpid(),getppid());
    //getpid() returns the process id of the executing process, getppid() returns the parent process id. 
    return 0;
}