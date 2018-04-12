/*************************************************************************
 * File     :   writev.c
 * Author   :   Saurabh Gupta
 * Desc     :   writev example c
 * Source   :   http://www.ccplusplus.com/2011/07/socket.html
 * Created  :   10:37 PM Saturday, February 18, 2012
 *************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/uio.h>

int main(int argc, char **argv) {
    static char part2[] = "THIS IS FROM WRITEV : http://www.ccplusplus.com/";
    static char part3[] = "]\n";
    static char part1[] = "[";
    struct iovec iov[3];

    iov[0].iov_base = part1;
    iov[0].iov_len = strlen(part1);

    iov[1].iov_base = part2;
    iov[1].iov_len = strlen(part2);

    iov[2].iov_base = part3;
    iov[2].iov_len = strlen(part3);

    writev(1, iov, 3);

    return 0;
}
/*
 *
 *
 [sgupta@rhel6x86 passing-creential-over-network]$ gcc writev.c -o writev
 [sgupta@rhel6x86 passing-creential-over-network]$ ./writev
 [THIS IS FROM WRITEV : http://www.ccplusplus.com/]
 [sgupta@rhel6x86 passing-creential-over-network]$
 */
