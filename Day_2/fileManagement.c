#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int source, dest;     
    char buffer[1024];   
    ssize_t bytesRead, bytesWritten;  

    
    source = open("exec.c", O_RDONLY);
    if (source == -1) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    
    dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1) {
        perror("Error opening destination file");
        close(source);  
        return EXIT_FAILURE;
    }

   
    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(dest, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(source);
            close(dest);
            return EXIT_FAILURE;
        }
    }


    if (bytesRead == -1) {
        perror("Error reading from source file");
    }

  
    close(source);
    close(dest);

    printf("File copied successfully.\n");

    return EXIT_SUCCESS;
}

/*

File Copying using I/O system calls
Author: GeorgeET15

open() - The open() system call is used to open files. It returns a file descriptor on success or -1 if there’s an error.
    - O_RDONLY: Opens the file for reading only.
    - O_WRONLY: Opens the file for writing only.
    - O_CREAT: Creates the file if it doesn’t already exist.
    - O_TRUNC: Truncates the file to zero length if it already exists.

read() - The read() system call reads data from a file descriptor into a buffer.
    - Returns the number of bytes read. If no more data is available, it returns 0.
    - Returns -1 on error.

write() - The write() system call writes data from a buffer to a file descriptor.
    - Returns the number of bytes written. If it’s less than expected, an error has occurred.

close() - The close() system call is used to close an open file descriptor, releasing any resources associated with it.

*/

