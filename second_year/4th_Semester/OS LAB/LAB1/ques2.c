#include<stdio.h>
#include<ctype.h>

int main(){
    int isContinue = 1;
    char c = 1;
    int cntr = 0;
    printf("Enter '&' for exit.\n");
    while(isContinue && c != '&'){
        c = getchar();
        if(c == '&'){
            isContinue = 0;
        }else if(!isalpha(c)){
            cntr++;
            putchar(c);
            printf("\n");
        }
        getchar();
    }

    fprintf(stderr, "\nnon-alphabatic charracter = %d" , cntr);
}