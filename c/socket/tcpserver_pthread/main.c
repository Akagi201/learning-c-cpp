#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * This will handle connection for each client
 */
void *connection_handler(void *socket_desc) {
    // Get the socket descriptor
    int sock = *(int *)socket_desc;
    int read_size;
    char *message;
    char client_message[2000] = {};

    // Send some messages to the client
    message = "Greetings! I am your connection handler.\n";
    write(sock, message, strlen(message));

    message = "Now type something and I shall repeat what you type.\n";
    write(sock, message, strlen(message));

    // Receive a message from client
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        // Send the message back to client
        write(sock, client_message, strlen(client_message));
    }

    if (read_size == 0) {
        puts("Client disconnected.");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed.");
    }

    // Free the socket pointer
    free(socket_desc);

    return 0;
}

int main(int argc, char *argv[]) {
    int socket_desc;
    int new_socket;
    int c;
    int *new_sock;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char *message;
    int ret = -1;
    int on = 1;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
    }

    // Prepare the sockaddr_in struct
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    ret = setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret < 0) {
        perror("setsockopt SO_REUSEADDR failed.");
    }

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections....");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("Connection accepted");

        // Reply to the client
        message = "Hello Client, I have received your connection. And now I will assign a handler for you\n";
        write(new_socket, message, strlen(message));

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *)new_sock) < 0) {
            perror("Could not create thread");
            return 1;
        }

        // Now join the thread, so that we don't terminate before the thread
        pthread_join(sniffer_thread, NULL);
        puts("Handler assigned");
    }

    if (new_socket < 0) {
        perror("Accept failed");
        return 1;
    }

    return 0;
}