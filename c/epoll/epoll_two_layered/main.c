#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

#define TEST_TIMEOUT (0)

static void print_events(const struct epoll_event *evts, int event_count) {
	int i;
	for (i = 0; i < event_count; i++) {
		printf("Event %d: %s, events=0x%x\n", i,
		       (const char *)evts[i].data.ptr, evts[i].events);
	}
}

int main() {
	struct epoll_event evt;
	struct epoll_event retrieved_evts[3];
	int thepipe[2];
	int epfd_master;
	int epfd_slave;
	int event_count;

	epfd_slave = epoll_create1(0);
	if (epfd_slave < 0) {
		perror("Slave epoll_create failed");
		return 1;
	}

	epfd_master = epoll_create1(0);
	if (epfd_master < 0) {
		perror("Master epoll_create failed");
		return 1;
	}

	evt.events = EPOLLIN | EPOLLOUT;
	evt.data.ptr = "slave epoll";
	if (epoll_ctl(epfd_master, EPOLL_CTL_ADD, epfd_slave, &evt) != 0) {
		perror("Master EPOLL_CTL_ADD failed");
		return 1;
	}

	printf("Querying epoll events on master (empty set)...");
	event_count = epoll_wait(epfd_master, retrieved_evts, 3, TEST_TIMEOUT);
	if (event_count >= 0) {
		printf(" got %d\n", event_count);
		print_events(retrieved_evts, event_count);
	} else {
		perror(" failed");
	}

	if (pipe(thepipe) != 0) {
		perror("pipe failed");
		return 1;
	}

	evt.events = EPOLLIN;
	evt.data.ptr = "pipe reading end";
	if (epoll_ctl(epfd_slave, EPOLL_CTL_ADD, thepipe[0], &evt) != 0) {
		perror("Slave EPOLL_CTL_ADD for reading end failed");
		return 1;
	}

	evt.events = EPOLLOUT;
	evt.data.ptr = "pipe writing end";
	if (epoll_ctl(epfd_slave, EPOLL_CTL_ADD, thepipe[1], &evt) != 0) {
		perror("Slave EPOLL_CTL_ADD for writing end failed");
		return 1;
	}

	printf("Querying epoll events on master (writer only)...");
	event_count = epoll_wait(epfd_master, retrieved_evts, 3, TEST_TIMEOUT);
	if (event_count >= 0) {
		printf(" got %d\n", event_count);
		print_events(retrieved_evts, event_count);
	} else {
		perror(" failed");
	}

	printf("Querying epoll events on slave (writer only)...");
	event_count = epoll_wait(epfd_slave, retrieved_evts, 3, TEST_TIMEOUT);
	if (event_count >= 0) {
		printf(" got %d\n", event_count);
		print_events(retrieved_evts, event_count);
	} else {
		perror(" failed");
	}

	if (write(thepipe[1], "hello", 5) < 0) {
		perror("write to the pipe failed");
	}

	printf("Querying epoll events on master (read available)...");
	event_count = epoll_wait(epfd_master, retrieved_evts, 3, TEST_TIMEOUT);
	if (event_count >= 0) {
		printf(" got %d\n", event_count);
		print_events(retrieved_evts, event_count);
	} else {
		perror(" failed");
	}

	printf("Querying epoll events on slave (read available)...");
	event_count = epoll_wait(epfd_slave, retrieved_evts, 3, TEST_TIMEOUT);
	if (event_count >= 0) {
		printf(" got %d\n", event_count);
		print_events(retrieved_evts, event_count);
	} else {
		perror(" failed");
	}

	close(epfd_master);
	close(epfd_slave);
	close(thepipe[1]);
	close(thepipe[0]);

	return 0;
}