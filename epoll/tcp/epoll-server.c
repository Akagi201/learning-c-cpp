#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"

#define LISTENQ (20)
#define MAXEVENTS LISTENQ

int main(int argc, char *argv[]) {
	int i, n;
	int listenfd, connfd, epfd, nfds;
	struct sockaddr_in servaddr, cliaddr;
	struct epoll_event ev, events[MAXEVENTS];
	bzero(&servaddr, sizeof(servaddr));

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		pr_exit("socket");
	}
	setnonblocking(listenfd);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		pr_exit("bind");
	}
	if (listen(listenfd, LISTENQ) < 0) {
		pr_exit("listen");
	}

	epfd = epoll_create(MAXEVENTS);
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
		pr_exit("epoll_ctl");
	}

	for (;;) {
		nfds = epoll_wait(epfd, events, MAXEVENTS, -1);
		for (i = 0; i < nfds; i++) {
			if (events[i].data.fd == listenfd) {
				socklen_t slen;
				if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr,
				                     &slen)) < 0) {
					pr_exit("accept");
				}
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			}
			if (events[i].events & EPOLLIN) {
				char buffer[MAXLINE];
				bzero(&buffer, MAXLINE);
				if ((n = read(events[i].data.fd, buffer, MAXLINE)) > 0) {
					if (buffer[n - 1] == '\n') {
						buffer[n - 1] = '\0';
					}
					printf("%s\n", buffer);
				}
			}
		}
	}
}
