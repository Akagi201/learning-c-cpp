#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int socket_desc = -1;
    int new_socket = -1;
    int c = 0;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char *message = NULL;
    int on = 1;
    int ret = -1;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket.\n");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret < 0) {
        perror("setsockopt SO_REUSEADDR failed.");
    }

    // Bind
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }

    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections....");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
        puts("Connection accepted");

        // Reply to the client
        message = "Hello Client, I have received your connection, but I have to go now, bye.\n";

        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);
        printf("client: ip: %s, port: %d\n", client_ip, client_port);

        write(new_socket, message, strlen(message));
        close(new_socket);
        new_socket = -1;
    }

    if (new_socket < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}




















