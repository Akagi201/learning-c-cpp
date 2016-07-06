
#include <stdio.h>

#include "hash.h"

int main() {
    hash_t *hash = hash_new();
    hash_set(hash, "name", (void *)"Akagi201");
    hash_set(hash, "age", (void *)"22");

    hash_each(hash, {
        printf("%s: %s\n", key, (char *) val);
    });

    hash_free(hash);

    return 0;
}