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
    int server_socket, client_socket, bind_status, listen_status, num1, num2, sum;
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    char SUM[BUFFER_SIZE];
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

    
        memset(buffer1, 0, BUFFER_SIZE);
        memset(buffer2, 0, BUFFER_SIZE);
        
        ssize_t bytes_received = read(client_socket, buffer1, BUFFER_SIZE - 1);
        buffer1[bytes_received] = '\0';
        num1 = atoi(buffer1);
        printf("Client: %d\n", num1);
        bzero(buffer1, strlen(buffer1));
        
        
        
        bytes_received = read(client_socket, buffer2, BUFFER_SIZE - 1);
        buffer2[bytes_received] = '\0';
        num2 = atoi(buffer2);
        printf("Client: %d\n", num2);
        bzero(buffer2, strlen(buffer2));
        
        sum = num1 + num2;
        
        printf("sum: %d\n", sum);
        
        
      
        
        //printf("You: ");
        //fgets(buffer, BUFFER_SIZE, stdin);
        //buffer[strcspn(buffer, "\n")] = '\0';
        //ssize_t bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
        
    
    close(client_socket);
    close(server_socket);
    return 0;
}
