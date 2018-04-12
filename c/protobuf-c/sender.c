#include <stdio.h>
#include <stdlib.h>
#include "mpb/amessage.pb-c.h"

int main(int argc, const char *argv[]) {
    Mpb__AMessage msg = MPB__AMESSAGE__INIT; // AMessage
    void *buf;                     // Buffer to store serialized data
    unsigned len;                  // Length of serialized data

    if (argc != 2 && argc != 3) {   // Allow one or two integers
        fprintf(stderr, "usage: amessage a [b]\n");
        return 1;
    }

    msg.a = atoi(argv[1]);
    if (argc == 3) {
        msg.has_b = 1;
        msg.b = atoi(argv[2]);
    }
    len = mpb__amessage__get_packed_size(&msg);

    buf = malloc(len);
    mpb__amessage__pack(&msg, buf);

    fprintf(stderr, "Writing %d serialized bytes\n", len); // See the length of message
    fwrite(buf, len, 1, stdout); // Write to stdout to allow direct command line piping

    free(buf); // Free the allocated serialized buffer
    return 0;
}
