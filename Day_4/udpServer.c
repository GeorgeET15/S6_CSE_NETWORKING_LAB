#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int server_socket, bind_status;
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

    
    bind_status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Chat with the Client\n");
    printf("--------------------\n\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        
        ssize_t bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE, MSG_WAITALL,
                                          (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received < 0) {
            perror("Receive failed");
            break;
        }

        buffer[bytes_received] = '\0'; 
        printf("Client: %s\n", buffer);

        
        if (strcmp(buffer, "bye") == 0) {
            printf("Client ended the chat\n");
            break;
        }

        
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  

        ssize_t bytes_sent = sendto(server_socket, buffer, strlen(buffer), MSG_CONFIRM,
                                    (const struct sockaddr *)&client_addr, client_addr_len);
        if (bytes_sent < 0) {
            perror("Send failed");
            break;
        }

      
        if (strcmp(buffer, "bye") == 0) {
            printf("You ended the chat\n");
            break;
        }
    }

   
    close(server_socket);
    return 0;
}

