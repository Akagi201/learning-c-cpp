#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "common.h"

#define IPADDRESS "127.0.0.1"

int main(int argc, char *argv[]) {
	int n;
	int connfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));

	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		pr_exit("socket");
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IPADDRESS);

	if (connect(connfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		pr_exit("connect");
	}

	for (;;) {
		bzero(&buffer, MAXLINE);
		if ((n = read(1, buffer, MAXLINE)) > 0) {
			if (send(connfd, buffer, n, 0) == n) {
				printf("send message: %s", buffer);
			}
		}
	}
}
