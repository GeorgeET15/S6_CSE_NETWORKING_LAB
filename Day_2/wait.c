#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void main () {

	if(fork() == 0) {
	
	
		printf("Hello from Child\n");
	}
	
	else {
	
		printf("Hello from parent\n");
		wait(NULL);
		printf("Child has terminated\n");
	}
	
	printf("return bye\n");


}
/*
Familiarization of wait() system call
Author: GeorgeET15

wait() :- A call to wait() blocks the calling process until one of its child processes exits or a signal is received. After the child process terminates, parent continues its execution after wait system call instruction. 


Child process may terminate due to any of these: 

    It calls exit();
    It returns (an int) from main
    It receives a signal (from the OS or another process) whose default action is to terminate.
    
    
    
In this code wait(NULL) is given to ignore the status otherwise we will have to intialise a stat variable and pass it.

eg: int stat
	wait(&stat)
	
	The status code will be stored in the variable.

*/
