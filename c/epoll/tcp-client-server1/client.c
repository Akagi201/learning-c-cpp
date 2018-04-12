#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int sock_connect(char *ip, char *port) {
	int res;
	int skfd;
	struct addrinfo hints, *result, *rp;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
	res = getaddrinfo(ip, port, &hints, &result);
	if (res != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		skfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (skfd == -1) {
			continue;
		}
		if (connect(skfd, rp->ai_addr, rp->ai_addrlen) != -1) {
			break;
		}
		close(skfd);
	}

	if (rp == NULL) {
		printf("Could not connect to %s!\n", ip);
		return -1;
	}

	freeaddrinfo(result);

	return skfd;
}

int main(int argc, char **argv) {
	int skfd, slen, rlen;
	char buf[128] = {0};
	char hostnm[64] = {0};
	time_t tm;

	if (argc != 3) {
		printf("Usage: ./epoll_clt [IP address] [Port number]\n");
		exit(EXIT_FAILURE);
	}

	skfd = sock_connect(argv[1], argv[2]);
	if (skfd == -1) {
		exit(EXIT_FAILURE);
	}

	if (gethostname(hostnm, sizeof(hostnm) - 1) == -1) {
		perror("get_host_name");
		exit(-1);
	}

	do {
		sleep(1);
		// send
		time(&tm);
		snprintf(buf, sizeof(buf), "From client %s %s", hostnm, ctime(&tm));
		// flag == 0: message don't wait
		slen = send(skfd, buf, strlen(buf), 0);
		if (slen != strlen(buf)) {
			printf("Send msg failed! slen (%d)\n", slen);
			break;
		}

		// recv
		memset(buf, 0, sizeof(buf));
		// flag == 0: message don't wait
		rlen = recv(skfd, buf, sizeof(buf), 0);
		if (rlen == -1) {
			printf("Recv message failed !\n");
			break;
		} else if (rlen == 0) {
			printf("Recv nothing!\n");
			break;
		} else {
			printf("Recv : %s\n", buf);
		}
	} while (1);

	close(skfd);
	return 0;
}
