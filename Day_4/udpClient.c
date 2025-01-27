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
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Chat with the Server\n");
    printf("--------------------\n\n");

    while (1) {
       
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  

        ssize_t bytes_sent = sendto(client_socket, buffer, strlen(buffer), MSG_CONFIRM,
                                    (const struct sockaddr *)&server_addr, server_addr_len);
        if (bytes_sent < 0) {
            perror("Send failed");
            break;
        }

        
        if (strcmp(buffer, "bye") == 0) {
            printf("You ended the chat\n");
            break;
        }

       
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, MSG_WAITALL,
                                          (struct sockaddr *)&server_addr, &server_addr_len);
        if (bytes_received < 0) {
            perror("Receive failed");
            break;
        }
        buffer[bytes_received] = '\0'; 
        printf("Server: %s\n", buffer);

        
        if (strcmp(buffer, "bye") == 0) {
            printf("Server ended the chat\n");
            break;
        }
    }

    
    close(client_socket);
    return 0;
}

