#include <stdio.h>
#include <stdlib.h>

void main() {
	
	int age;
	printf("Enter the your age: ");
	scanf("%d", &age);
	
	if (age < 18) {
	
		printf("You are a child\n");
		exit(1);		
	}
	
	else if (age >=18){
	
	
		printf("You are an adult\n");
	
	}
	
	
	printf("This line only executes if your age is >= 18\n");

}
/*

Familiarization of exit() system call
Author: GeorgeET15


exit() :- The C exit() function is a standard library function used to terminate the calling process. 
When exit() is called, any open file descriptors belonging to the process are closed and any children 
of the process are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.


void exit(int status);

The exit() function in C only takes a single parameter status which is the exit code that is returned to the caller i.e. 
either the operating system or parent process. There are two valid values we can use as the status each having a different 
meaning. They are as follows:


    0 or EXIT_SUCCESS: 0 or EXIT_SUCCESS means that the program has been successfully executed without encountering any error.
    1 or EXIT_FAILURE: 1 or EXIT_FAILURE means that the program has encountered an error and could be executed successfully.
    
When called, the exit() function in C performs the following operations:

    1) Flushes unwritten buffered data.
    2) Closes all open files.
    3) Removes temporary files.
    4) Returns an integer exit status to the operating system.

*/
