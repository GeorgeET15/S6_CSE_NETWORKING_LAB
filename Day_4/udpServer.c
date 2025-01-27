#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6000
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

/*
Server Program for UDP Chat Application
Author: GeorgeET15

Description:
This program creates a server using UDP (datagram-based communication), listens for messages
from the client, and enables two-way communication (chat) between the server and client.

Main Steps:

1. Socket Creation:
   - A socket is created using the `socket()` system call with the UDP protocol (SOCK_DGRAM).
   - The socket uses the IPv4 address family (AF_INET).

2. Binding the Socket:
   - The server binds the socket to a specific IP address and port using the `bind()` system call.
   - If binding fails, the server exits with an error message.

3. Chat Loop:
   - The server continuously listens for incoming messages from the client using the `recvfrom()` system call.
   - After receiving, the server prints the client's message.
   - The server sends a reply to the client using the `sendto()` system call.
   - The chat ends if either the client or the server sends the message "bye".

4. Cleanup:
   - After the chat ends, the server closes the socket using the `close()` system call.
   - The program terminates gracefully.

Key Functions Used:
- `socket()`: Creates a UDP socket.
- `bind()`: Binds the socket to an address and port.
- `recvfrom()`: Receives data from the client.
- `sendto()`: Sends data to the client.
- `close()`: Closes the socket.
*/

