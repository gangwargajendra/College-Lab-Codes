#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if(argc != 3){
        fprintf(stderr, "Missing Argument!");
        exit(1);
    }

    int p[2];
    if(pipe(p) == -1){
        perror("Pipe creation failed !");
        exit(1);
    }

    pid_t pid, pid1;
    pid = fork();

    if(pid < 0){
        perror("Fork Failed.");
        exit(1);
    }

    else if(pid == 0){
        close(p[1]);

        dup2(p[0], STDIN_FILENO);
        close(p[0]);

        execlp("./B", "B", argv[1], argv[2], NULL);
        perror("exclp failed for B!");

        exit(1);
    }

    pid1 = fork();

    if(pid1 < 0){
        perror("Fork Failed.");
        exit(1);
    }

    else if(pid1 == 0){
        close(p[0]);

        dup2(p[1], STDOUT_FILENO);
        close(p[1]);

        execlp("./C", "C", argv[1], argv[2], NULL);

        perror("exclp failed!");
    }
   else{
        close(p[0]);
        close(p[1]);
    }

    wait(NULL);
    wait(NULL);
    printf("Both child processes have completed.\n");

    return 0;
}