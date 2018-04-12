#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "strsplit.h"

int main(void) {
    {
        char str[] = "hello\nworld";
        char *parts[2] = {NULL};
        size_t size = strsplit(str, parts, "\n");
        assert(size);
        int i = 0;
        for (; i < size; i++) {
            printf("%s\n", parts[i]);
        }
        for (i = 0; i < (int) size; i++) {
            free(parts[i]);
        }
    }

    {
        char str[] = "0 1 2 3 4 5 6 7 8 9";
        char *parts[10] = {NULL};
        size_t size = strsplit(str, parts, " ");
        assert(size);
        int i = 0;

        for (; i < (int) size; i++) {
            assert(i == atoi(parts[i]));
            printf("%s\n", parts[i]);
        }

        for (i = 0; i < (int) size; i++) {
            free(parts[i]);
        }
    }

    return 0;
}
