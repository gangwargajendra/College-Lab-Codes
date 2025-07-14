#include<stdio.h>
#include<ctype.h>

int main(){
    int isContinue = 1;
    char c = 1;
    printf("Enter '&' for exit.\n");
    while(isContinue && c != '&'){
        c = getchar();
        if(c == '&'){
            isContinue = 0;
            printf("Exit.");
        }else if(islower(c)){
            printf("upper case of %c is : %c\n",c , toupper(c));
        }else if(isupper(c)){
            printf("upper case of %c is : %c\n",c ,tolower(c));
        }else{
            printf("Enter character is : %c\n", c);
        }
        getchar();
    }
    return 0;
}