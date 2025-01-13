#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;               
    struct dirent *entry;   

 
    dir = opendir(".");  
    if (dir == NULL) { 
        perror("opendir"); 
        return EXIT_FAILURE;  
    }

  
    printf("Directory contents:\n");
    while ((entry = readdir(dir)) != NULL) {  
        printf("%s\n", entry->d_name);
    }

    
    closedir(dir); 

    return EXIT_SUCCESS;  
}

/*

Familiarization of opendir(), readdir(), and closedir() system calls
Author: GeorgeET15

opendir() :- This function is used to open a directory stream. It returns a pointer to a DIR structure which is used in 
subsequent operations (such as reading the contents of the directory). If the directory cannot be opened, it returns NULL.
The argument to opendir is the name of the directory to open. Here, we use "." to represent the current directory.

    Syntax: DIR *opendir(const char *name);
    
    Returns:
    - A pointer to a DIR structure if successful.
    - NULL if there is an error (e.g., the directory does not exist).

readdir() :- This function reads the next directory entry in a directory stream. It returns a pointer to a struct dirent 
that contains information about the entry. The loop continues until readdir returns NULL, indicating no more entries are available.

    Syntax: struct dirent *readdir(DIR *dirp);
    
    Returns:
    - A pointer to struct dirent for the current directory entry.
    - NULL when the end of the directory is reached.

struct dirent is a structure that contains various fields describing the directory entry. The most commonly used field is:
- d_name: A string representing the name of the file or directory.

closedir() :- This function closes the directory stream that was opened by opendir. It frees the resources used for reading the directory 
and should be called when the directory is no longer needed.

    Syntax: int closedir(DIR *dirp);
    
    Returns:
    - 0 on success.
    - -1 on failure, with errno set appropriately.


*/

