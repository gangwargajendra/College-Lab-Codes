#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int main() {
    pid_t child_pid;

    // 1. Create a child process using fork()
    child_pid = fork();

    

    if (child_pid == 0) {
        // This is the child process
        printf("Child process (PID: %d) is running.\n", getpid());

        // Child process does some work or keeps running in a loop
        while(1) {
           sleep(1);
           printf("Child is working...\n");
        }

        exit(EXIT_SUCCESS); // Should not reach here
    } else {
        // This is the parent process
        printf("Parent process (PID: %d) is running.\n", getpid());
        printf("Child process created with PID: %d\n", child_pid);
       
        sleep(5); // Wait for 5 seconds to let the child run

        // 2. Send SIGTERM signal to the child process using kill()
        int result = kill(child_pid, SIGTERM);

        if (result == 0) {
             printf("SIGTERM signal sent to child process (PID: %d)\n", child_pid);
        } 

        // 3. Wait for the child process to terminate
        int status;
        pid_t waited_pid = wait(&status);

       /* if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited normally with status: %d\n", waited_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process (PID: %d) terminated by signal: %d\n", waited_pid, WTERMSIG(status));
        } else {
            printf("Child process (PID: %d) terminated abnormally.\n", waited_pid);
        }

        return EXIT_SUCCESS;*/
    }
}