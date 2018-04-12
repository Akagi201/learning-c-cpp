#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <strings.h>

int main() {
    char foo[4];
    char bar[5];
    char baz[4];

    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    fd = open("groad.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    /* set up our iovec structures */
    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    /* read into the structures with a single call */
    nr = readv(fd, iov, 3);
    if (nr == -1) {
        perror("readv");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        printf("%s", (char *) iov[i].iov_base);
        printf("\n");
    }

    if (close(fd)) {
        perror("close");
        return 1;
    }

    return 0;
}