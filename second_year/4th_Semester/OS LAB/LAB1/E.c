#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>

jmp_buf env;
pid_t pid1, pid2;

void alarm_handler(int sig) {
    fprintf(stderr, "\nTimeout! Killing both children.\n");
    kill(pid1, SIGTERM);
    kill(pid2, SIGTERM);
    longjmp(env, 1);
}

void sigterm_handler(int sig) {
    fprintf(stderr, "I've been killed!\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int p[2];
    char *file1 = NULL, *file2 = NULL, *n_arg = NULL;
    int n_value = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            n_arg = argv[i];
        } else if (!file1) {
            file1 = argv[i];
        } else {
            file2 = argv[i];
        }
    }

    if (n_arg) {
        n_value = atoi(n_arg + 1);
        if (n_value <= 0) {
            fprintf(stderr, "Invalid -n argument. Must be a positive integer.\n");
            exit(2);
        }
    }

    if (pipe(p) == -1) {
        perror("Pipe failed!");
        exit(1);
    }

    signal(SIGALRM, alarm_handler);
    signal(SIGTERM, sigterm_handler);

    if (setjmp(env) == 0) {
        alarm(15); 
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork Failed");
        exit(1);
    } else if (pid1 == 0) {
        fprintf(stderr, "B(count child) PID: %d\n", getpid());
        signal(SIGTERM, sigterm_handler);
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);
        if (n_arg) {
            execlp("./B", "B", argv[1], argv[2], NULL);
        } else {
            execlp("./B", "B", argv[1], argv[2], NULL);
        }
        perror("execlp count failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork Failed");
        exit(1);
    } else if (pid2 == 0) {
        fprintf(stderr, "C(convert child) PID: %d\n", getpid());
        signal(SIGTERM, sigterm_handler);
        signal(SIGPIPE, sigterm_handler);
        close(p[1]);
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        execlp("./C", "C", argv[1], argv[2], NULL);
        perror("execlp failed for convert!");
        exit(1);
    }

    if (file1 && !file2) {
        FILE *fp = fopen(file1, "r");
        if (!fp) {
            perror("File open failed");
            kill(pid1, SIGTERM);
            kill(pid2, SIGTERM);
            exit(1);
        }
        dup2(fileno(fp), STDIN_FILENO);
        fclose(fp);
    }

    close(p[0]);
    close(p[1]);

    int status;
    pid_t exited_child;

    while ((exited_child = wait(&status)) > 0) {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 2) {
            fprintf(stderr, "Child %d exited abnormally. Killing other child.\n", exited_child);
            kill(exited_child == pid1 ? pid2 : pid1, SIGTERM);
            wait(NULL);
            exit(1);
        }
    }

    fprintf(stderr, "Both children exited normally.\n");
    exit(0);
}
