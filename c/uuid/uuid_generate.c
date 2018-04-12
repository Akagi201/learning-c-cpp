#include <stdio.h>
#include <uuid/uuid.h>

int main(int argc, char **argv) {
    uuid_t uuid;
    uuid_generate(uuid);

    unsigned char *p = uuid;
    int i;
    for (i = 0; i < sizeof(uuid_t); i++, p++) {
        printf("%02x", *p);
    }
    printf("\n");

    return 0;
}
