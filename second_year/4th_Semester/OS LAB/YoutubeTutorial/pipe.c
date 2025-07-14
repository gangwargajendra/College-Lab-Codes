#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int fd[2];  // file discripter
    // fd[0]: read fd[1]: write
    if (pipe(fd) == -1){   // it is like a buffer to store the data
        printf("An error occured with opening the pipe\n");
        return 1;
    }
    int id = fork();
    if(id == 0) {
        close(fd[0]);
        int x;
        printf("Input a number : ");
        scanf("%d",&x);
        if (write(fd[1], &x, sizeof(int)) == -1){
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        close(fd[1]);
    }else {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1){
            printf("An error occured with reading to the pipe\n");
            return 3;
        }
        close(fd[0]);
        printf("Got from the child process %d\n",y);
    }

    return 0;
}