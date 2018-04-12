#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

int main() {
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    char *buf[] = {".net", "groad", "www."};

    fd = open("groad.txt", O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    /* fill out three iovec structures */
    for (i = 0; i < 3; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]);
        printf("%d : %d\n", i, iov[i].iov_len);
    }

    /* write a single call, write them all out */
    nr = writev(fd, iov, 3);
    if (nr == -1) {
        perror("writev");
        return 1;
    }
    printf("wrote %d bytes\n", nr);

    if (close(fd)) {
        perror("close");
        return 1;
    }

    return 0;
}