
/* A simple Menue Driven program to implement System Calls */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main () {
	
	int selection;
	printf("System Calls Executer\n");
	printf("---------------------\n\n");
	char *args[] = { "./fork", "./exec", "./exit", "./wait", NULL };
	
	
	while (1) {
	
		printf("System Calls Available\n\n");
		printf("1) FORK\n2) EXEC\n3) EXIT\n4) WAIT\n5) Exit\n\n");
		printf("Enter the number to execute: ");
		scanf("%d", &selection);
		
		switch(selection) {
		
			case 1: 
					execvp(args[selection-1], args);
					printf("FORK is executed\n");
					break;
			case 2: 
					execvp(args[selection-1], args);
					printf("EXEC is executed\n");
					break;
			case 3: 
					execvp(args[selection-1], args);
					printf("EXIT is executed\n");
					break;
			case 4: 
					execvp(args[selection-1], args);
					printf("WAIT is executed\n");
					break;
			case 5: 
					return (0);
			default: 
					printf("Invalid Input\n\n");
					
		
		
		}
	
	
	}
	
	

}
