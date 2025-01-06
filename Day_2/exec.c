#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void main() {

	char *args[] = { "./ftbe", NULL};
	execvp(args[0], args);
	
	printf("exec.c is executed\n");
	

}
/*

Familiarization of exec commands
Author: GeorgeET15


The exec family of functions replaces the current running process with a new process. 
It can be used to run a C program by using another C program.

execvp() :- Using this command, the created child process does not have to run the same 
program as the parent process does. The exec type system calls allow a process to run any
program files, which include a binary executable or a shell script . 

SYNTAX : int execvp (const char *file, char *const argv[]);

	file :- points to the file to be executed.
	argv :- is a null terminated array of character pointers.

In this code "./ftbe" is a another c program file fileToBeEcecuted.c 's executable file.

	cc filetobeExecuted.c -o ftbe
*/
