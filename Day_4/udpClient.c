#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6000
#define SERVER_IP "127.0.0.2"
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
/*
Client Program for UDP Chat Application
Author: GeorgeET15

Description:
This program creates a client using UDP (datagram-based communication), connects to the server,
and enables two-way communication (chat) between the client and server.

Main Steps:

1. Socket Creation:
   - A socket is created using the `socket()` system call with the UDP protocol (SOCK_DGRAM).
   - The socket uses the IPv4 address family (AF_INET).

2. Configuring the Server Address:
   - The client sets up the server's IP address and port using the `server_addr` structure.
   - The `inet_pton()` function is used to convert the server's IP address from text to binary form.

3. Chat Loop:
   - The client continuously sends messages to the server using the `sendto()` system call.
   - After sending a message, the client waits for a response using the `recvfrom()` system call.
   - The chat ends if either the client or the server sends the message "bye".

4. Cleanup:
   - After the chat ends, the client closes the socket using the `close()` system call.
   - The program terminates gracefully.

Key Functions Used:
- `socket()`: Creates a UDP socket.
- `inet_pton()`: Converts an IP address from text to binary form.
- `sendto()`: Sends data to the server.
- `recvfrom()`: Receives data from the server.
- `close()`: Closes the socket.
*/


