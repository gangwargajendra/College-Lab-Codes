#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal. Signal number: %d\n", signum);
}

int main() {
    pid_t pid;

    // Set up the signal handler for SIGUSR1 
    // A user-defined signal with no predefined meaning
    signal(SIGUSR1, sigusr1_handler);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        sleep(2); // Wait for the parent to send the signal
        printf("Child process exiting.\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process (PID: %d) sending SIGUSR1 to child (PID: %d).\n", getpid(), pid);
        sleep(1); // Give the child time to set up
        if (kill(pid, SIGUSR1) == 0) {
            printf("Signal SIGUSR1 sent successfully.\n");
        } else {
            perror("Failed to send signal");
        }

        // Wait for the child process to exit
        wait(NULL);
        printf("Parent process exiting.\n");
    }

    return 0;
}