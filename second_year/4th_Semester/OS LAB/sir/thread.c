#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//to compile use -pthread option
void* t_runner(void* arg)
{
	
	printf("%s from thread\n",(char *)arg);

	pthread_exit(0);
}

int main()
{

	// Thread ID:
	pthread_t tid;
    char *msg="Hello";
	// Create attributes
	pthread_attr_t attr;

    //initialise attributes 
	pthread_attr_init(&attr);

    //create thread, here t_runner is function which will be executed by the created thread and msg is the parameter passed to the thead/funtion 

	pthread_create(&tid, &attr, t_runner, msg);

    //	Wait for the thread to complete
	pthread_join(tid, NULL);

	printf("Back to main thread");

}