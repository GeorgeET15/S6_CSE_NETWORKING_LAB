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
    int server_socket, client_socket, bind_status, listen_status;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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

    listen_status = listen(server_socket, 3);
    if (listen_status < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    
    printf("Listening to open ports......\n\n");

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        perror("Accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to client successfully:\n\n");

	printf("Chat with the Client\n");
	printf("--------------------\n\n");
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (bytes_received < 0) {
            perror("Read failed");
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
        ssize_t bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
        if (bytes_sent < 0) {
            perror("Send failed");
            break;
        }

        if (strcmp(buffer, "bye") == 0) {
            printf("You ended the chat\n");
            break;
        }
    }

    close(client_socket);
    close(server_socket);
    return 0;
}
/*

Server Program for Chat Application
Author: GeorgeET15

Description:
This program creates a server that listens for connections from a client, establishes a socket connection,
and enables two-way communication (chat) between the server and client.

Main Steps:

1. Socket Creation:
   - A socket is created using the `socket()` system call.
   - The socket uses the IPv4 address family (AF_INET) and TCP protocol (SOCK_STREAM).

2. Binding the Socket:
   - The server binds the socket to a specific IP address and port using the `bind()` system call.
   - If binding fails, the server exits with an error message.

3. Listening for Connections:
   - The server listens for incoming client connections using the `listen()` system call.
   - A backlog of 3 connections is specified.

4. Accepting a Connection:
   - The server accepts a connection from a client using the `accept()` system call.
   - This creates a new socket dedicated to the client communication.

5. Chat Loop:
   - The server continuously reads messages from the client using the `read()` system call.
   - After reading, the server prints the client's message.
   - The server sends a reply to the client using the `send()` system call.
   - The chat ends if either the client or the server sends the message "bye".

6. Cleanup:
   - After the chat ends, the server closes both the client and server sockets using the `close()` system call.
   - The program terminates gracefully.

Key Functions Used:
- `socket()`: Creates a socket.
- `bind()`: Binds the socket to an address and port.
- `listen()`: Prepares the socket to accept incoming connections.
- `accept()`: Accepts an incoming client connection.
- `read()`: Reads data from the client.
- `send()`: Sends data to the client.
- `close()`: Closes the socket.

*/


