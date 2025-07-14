#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    fork();//creates a duplicate child  process
    fork();//child process starts execution from next statement
    printf("Hello\n");

    return 0;
}