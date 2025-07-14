#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file for reading
    int file = open("input.txt", O_RDONLY);
    if (file < 0) {
        perror("open");
        exit(1);
    }

    // Redirect stdin to read from the file
    dup2(file, STDIN_FILENO);
    close(file); // Close original file descriptor (not needed anymore)

    // Now, all standard input reads will come from "input.txt"
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("Read from file: %s", buffer);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("open");
        exit(1);
    }

    // Redirect stdout to output.txt
    dup2(file, STDOUT_FILENO);

    // Now, all printf output goes to output.txt instead of the terminal
    printf("This will be written to output.txt\n");

    close(file);
    return 0;
}
