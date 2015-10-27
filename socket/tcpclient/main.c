#include <stdio.h>
#include <string.h> // strlen
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr

int main(int argc, char *argv[]) {
    int socket_desc = -1;
    struct sockaddr_in server;
    char *message = NULL;
    char server_reply[2000] = {};

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
    }

    // use the address of baidu.com to connect test.
    server.sin_addr.s_addr = inet_addr("115.239.211.112");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    // Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connect error\n");
        return 1;
    }

    printf("Connected\n");

    // Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        printf("Send failed.\n");
        return 1;
    }

    printf("Data Send\n");

    // Receive a reply from the server
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        printf("recv failed.\n");
    }

    printf("Reply received.\n");
    puts(server_reply);

    close(socket_desc);
    return 0;
}
