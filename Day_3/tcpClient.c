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
    int client_socket, connection_status;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    connection_status = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connection_status < 0) {
        perror("Connection to the server failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server successfully:\n\n");
	
	printf("Chat with the Server\n");
	printf("--------------------\n\n");
    while (1) {
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

        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (bytes_received < 0) {
            perror("Read failed");
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

Client Program for Chat Application
Author: GeorgeET15

Description:
This program creates a client that connects to a server over a socket and enables two-way communication (chat) with the server.

Main Steps:

1. Socket Creation:
   - A socket is created using the `socket()` system call.
   - The socket uses the IPv4 address family (AF_INET) and TCP protocol (SOCK_STREAM).

2. Defining Server Address:
   - The server's IP address and port are defined.
   - The `inet_pton()` system call converts the human-readable IP address into binary form.
   - If the IP address is invalid, the client exits with an error message.

3. Connecting to the Server:
   - The client connects to the server using the `connect()` system call.
   - If the connection fails, the client exits with an error message.

4. Chat Loop:
   - The client continuously sends messages to the server using the `send()` system call.
   - After sending, the client waits for a reply from the server using the `read()` system call.
   - The client's message is entered via standard input (`stdin`).
   - The chat ends if either the client or the server sends the message "bye".

5. Cleanup:
   - After the chat ends, the client closes the socket using the `close()` system call.
   - The program terminates gracefully.

Key Functions Used:
- `socket()`: Creates a socket.
- `inet_pton()`: Converts an IP address from text to binary form.
- `connect()`: Establishes a connection to the server.
- `send()`: Sends data to the server.
- `read()`: Reads data from the server.
- `close()`: Closes the socket.

*/

