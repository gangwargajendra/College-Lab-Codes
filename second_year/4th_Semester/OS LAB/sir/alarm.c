#include<stdio.h>
#include<unistd.h>
#include<signal.h>
 
void a(int signum){
    printf("Inside handler function\n");
}
 
int main(){
 
    signal(SIGALRM,a); // Register signal handler
 
    alarm(2);  // Scheduled alarm after 2 seconds
    alarm(4);  // override the previous alarm with a new one after 4 seconds
    for(int i=1;i<9;i++){
        printf("%d : Inside main function\n",i);
        sleep(1);  // Delay for 1 second
    }

    return 0;
}