#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000         
#define BUFFER_SIZE 1024    


long factorial(int n) {
    long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int server_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

  
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

  
    server_addr.sin_family = AF_INET;              
    server_addr.sin_port = htons(PORT);             
    server_addr.sin_addr.s_addr = INADDR_ANY;       

    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for a number from the client...\n");

    while (1) {

        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(server_socket, buffer, BUFFER_SIZE, MSG_WAITALL,
                 (struct sockaddr *)&client_addr, &client_addr_len);

       
        int number = atoi(buffer);
        printf("Received number: %d\n", number);

        
        long result = factorial(number);
        printf("Calculated factorial: %ld\n", result);

  
        sprintf(buffer, "%ld", result); 
        sendto(server_socket, buffer, strlen(buffer), MSG_CONFIRM,
               (struct sockaddr *)&client_addr, client_addr_len);
    }

    close(server_socket);
    return 0;
}

