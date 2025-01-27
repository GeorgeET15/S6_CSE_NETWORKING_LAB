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
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

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
	
        printf("Enter int 1: ");
        fgets(buffer1, BUFFER_SIZE, stdin);
        buffer1[strcspn(buffer1, "\n")] = '\0';
        
        printf("Enter int 2: ");
        fgets(buffer2, BUFFER_SIZE, stdin);
        buffer2[strcspn(buffer2, "\n")] = '\0';
        
        
        ssize_t bytes_sent = send(client_socket, buffer1, strlen(buffer1), 0);
        if (bytes_sent < 0) {
            perror("Send failed");
            
        }
		
		bytes_sent = send(client_socket, buffer2, strlen(buffer2), 0);
        if (bytes_sent < 0) {
            perror("Send failed");
            
        }

        memset(buffer1, 0, BUFFER_SIZE);
        memset(buffer1, 0, BUFFER_SIZE);
        //ssize_t bytes_received = read(client_socket, buffer, BUFFER_SIZE - 1);
        //if (bytes_received < 0) {
            //perror("Read failed");
            
        //}
        //buffer[bytes_received] = '\0';
        //printf("Server: %s\n", buffer);

        
    

    close(client_socket);
    return 0;
}
