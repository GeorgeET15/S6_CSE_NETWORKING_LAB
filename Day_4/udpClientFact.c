#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000         
#define SERVER_IP "127.0.0.1" 
#define BUFFER_SIZE 1024   

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t server_addr_len = sizeof(server_addr);


    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    server_addr.sin_family = AF_INET;           
    server_addr.sin_port = htons(PORT);         
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr); 


    printf("Enter a number: ");
    fgets(buffer, BUFFER_SIZE, stdin);          
    buffer[strcspn(buffer, "\n")] = '\0';      

    sendto(client_socket, buffer, strlen(buffer), MSG_CONFIRM,
           (struct sockaddr *)&server_addr, server_addr_len);

   
    memset(buffer, 0, BUFFER_SIZE); 
    recvfrom(client_socket, buffer, BUFFER_SIZE, MSG_WAITALL,
             (struct sockaddr *)&server_addr, &server_addr_len);


    printf("Factorial: %s\n", buffer);

    close(client_socket);
    return 0;
}

