#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

int main(int argc, char* argv[]) {
    if(argc != 3){
        perror("Argument missmatch.");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("Error in opening input file.");
        exit(1);
    }


    FILE* fp1 = fopen(argv[2], "w");
    if(fp1 == NULL){
        perror("Error in opening output file.");
        fclose(fp);
        exit(1);
    }

    int ch = 0;

    while((ch = fgetc(fp)) != EOF){
        if(islower((char) ch)) {
            fputc(toupper(ch), fp1);
        }
        else if(isupper(ch)) {
            fputc(tolower(ch), fp1);
        }
        else{
            fputc(ch, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    return 0;
}





