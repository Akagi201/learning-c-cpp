#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BACKLOG 10
#define MAXEVENTS 10
#define DATALEN 64

int setnonblocking(int fd) {
	int opt;

	opt = fcntl(fd, F_GETFL, 0);
	if (opt == -1) {
		perror("fcntl");
		return -1;
	}
	opt |= O_NONBLOCK;
	opt = fcntl(fd, F_SETFL, opt);
	if (opt == -1) {
		perror("fcntl");
		return -1;
	}

	return 0;
}

int listen_socket(char *port) {
	int res;
	int skfd;
	int opt = 1;
	struct addrinfo hints, *result, *rp;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	res = getaddrinfo(NULL, port, &hints, &result);
	if (res != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		skfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (skfd == -1) {
			continue;
		}

		if (setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) ==
		    -1) {
			perror("setsockopt");
			close(skfd);
		}

		if (bind(skfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			printf("Bind success!\n");
			break;
		}
		close(skfd);
	}

	if (rp == NULL) {
		printf("Fail to find socket !\n");
		return -1;
	}

	if (listen(skfd, BACKLOG) == -1) {
		printf("Fail to listen !\n");
		close(skfd);
		return -1;
	}

	freeaddrinfo(result);

	return skfd;
}

int main(int argc, char **argv) {
	int skfd, rskfd;
	int efd;
	int nefd;
	int rlen, slen;
	char ip[INET_ADDRSTRLEN];
	char buf[DATALEN];
	socklen_t addrlen;
	struct epoll_event ev, *evp;
	struct sockaddr acpaddr;

	if (argc != 2) {
		printf("Usage: ./epoll_svr [Port number]\n");
		exit(0);
	}

	skfd = listen_socket(argv[1]);
	if (skfd == -1) {
		return -1;
	}

	efd = epoll_create1(0); // epoll create
	if (efd == -1) {
		close(skfd);
		perror("epoll_create1");
		return -1;
	}

	/* epoll struct setting */
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.fd = skfd; // epoll fd == sockfd
	/* registered skfd to epoll event */
	if (epoll_ctl(efd, EPOLL_CTL_ADD, skfd, &ev) == -1) {
		close(efd);
		close(skfd);
		perror("epoll_ctl_add");
		return -1;
	}

	evp = calloc(MAXEVENTS, sizeof(struct epoll_event));
	if (evp == NULL) {
		printf("Calloc Fialed!\n");
		close(efd);
		close(skfd);
		return -1;
	}

	do {
		/*
		 * Wait I/O event, like select
		 * stored the event into `evp`
		 */
		nefd = epoll_wait(efd, evp, MAXEVENTS, -1);
		if (nefd == -1) {
			perror("epoll_wait");
			close(efd);
			close(skfd);
			return -1;
		}

		// find the trigger event fd in `evp` array
		for (int n = 0; n != nefd; ++n) {
			/*
			 *trigger fd is skfd, means there are someone who wanan connect
			 */
			if (evp[n].data.fd == skfd) {
				addrlen = sizeof(acpaddr);
				// accept
				rskfd = accept(skfd, &acpaddr, &addrlen);
				if (rskfd == -1) {
					close(efd);
					close(skfd);
					close(nefd);
					perror("accept");
					return -1;
				}
				struct sockaddr_in *tmp = (struct sockaddr_in *)&acpaddr;
				inet_ntop(AF_INET, &tmp->sin_addr, ip, sizeof(ip));
				printf("Connect with IP %s\n", ip);
				if (setnonblocking(rskfd) == -1) {
					close(efd);
					close(rskfd);
					close(nefd);
					return -1;
				}
				// accept end
				ev.events =
				    EPOLLIN | EPOLLOUT | EPOLLET; // set rskfd epoll event
				ev.data.fd = rskfd;               // epool the recv socket fd
				if (epoll_ctl(efd, EPOLL_CTL_ADD, rskfd, &ev) == -1) {
					perror("epoll_ctl");
					return -1;
				}
			} else {
				// event `recv` trigger
				if (evp[n].events & EPOLLIN) {
					memset(buf, 0, sizeof(buf));
					rlen = recv(evp[n].data.fd, buf, sizeof(buf) - 1, 0);
					if (rlen == -1) {
						printf("Recv failed!\n");
						close(evp[n].data.fd);
						return -1;
					}
					printf("Recv : %s (%d)\n", buf, rlen);
				}
				// event `send` trigger
				if (evp[n].events & EPOLLOUT) {
					slen = send(evp[n].data.fd, "Here is Server", 14, 0);
					if (slen == -1) {
						printf("Send Failed !\n");
						close(evp[n].data.fd);
						return -1;
					}
					printf("Send %d\n", slen);
				}
				// Unknow events
				if ((evp[n].events & EPOLLERR) == EPOLLERR ||
				    (evp[n].events & EPOLLHUP) == EPOLLHUP ||
				    ((evp[n].events & EPOLLIN) != EPOLLIN &&
				     (evp[n].events & EPOLLOUT) != EPOLLOUT)) {
					printf("Unknown event: %d\n", evp[n].events);
					close(evp[n].data.fd);
					return -1;
				}
			}
		}
	} while (1);

	free(evp);
	close(rskfd);

	return 0;
}
