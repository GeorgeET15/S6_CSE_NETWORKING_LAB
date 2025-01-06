#include <stdio.h>
#include <unistd.h>

void main() {

	pid_t child_pid;
	
	child_pid = fork();
	
	if(child_pid == 0) {
	
		printf("Child process, PID :- %d\n", getpid());
	}
	
	else if (child_pid > 0 ) {
	
		printf("Parent Process, PID :- %d\n", getpid());
	
	}
	else {
	
		printf("Fork failed");
	}
}
/*

Familiarization of fork() and getpid() system calls
Author: GeorgeET15

1) fork() :- is a system call in the Operating System used to create a copy of the process, 
the copied process created is known as the child process. The main process or the process 
from which the child process is created is known as the parent process. The parent and child 
processes are in separate address spaces in fork(). A Child process will have its Process ID 
different from the parent's ID.


Total no. of child process generated will be: 2^n – 1.
Total no of processes executed: 2^n.

Here n is the number of times forks called.

fork() returns 3 values 0, 1, -1. 0 means it is child process 1 or greater than 1 means it is parent process and -1 means some error occured.


2) getpid() :- returns the process ID of the parent of the calling process. If the calling process 
was created by the fork() function and the parent process still exists at the time of the getppid 
function call, this function returns the process ID of the parent process. Otherwise, this function 
returns a value of 1 which is the process id for init process.

*/
