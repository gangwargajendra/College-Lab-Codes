#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 3) {
        fprintf(stderr, "Argument Error!");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if(input == NULL){
        perror("Error in opening file.");
        return 1;
    }

    FILE* output = fopen(argv[2], "w");
    if(output == NULL){
        perror("Error in openeing output file.");
        fclose(input);
        return 1;
    }

    int ch = 0;
    int nonAlpha = 0;

    while ((ch = fgetc(input)) != EOF) {
        if (!isalpha(ch)) {
            nonAlpha++;
        }
        fputc(ch, output);
    }

    fprintf(stderr, "Non-alphabetic character count: %d\n", nonAlpha);

    fclose(input);
    fclose(output);

    return 0;
}