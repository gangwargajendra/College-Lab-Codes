#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char* agrv){
    _execl("./exec.c", "./exec", "google.com", NULL);
    
    return 0;
}