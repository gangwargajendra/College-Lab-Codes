#include <stdio.h>
#include <unistd.h>  // For fork() and exec() system calls
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("This is the child process.\n");
        // execlp("/bin/echo", "echo", "Hello from exec!", NULL);  // Replace child with `echo` command
    } else {
        // Parent process
        printf("This is the parent process. Child PID: %d\n", pid);
    }

    return 0;
}
