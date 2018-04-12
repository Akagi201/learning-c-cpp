/*
 * g++ memory_error_notcmalloc.cpp -g -O0 -o memory_error_notcmalloc
 * Refs: http://blog.csdn.net/win_lin/article/details/50461709
 */
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void foo(char *p) {
    memcpy(p, "01234567890abcdef", 16);
}

int main(int argc, char **argv) {
    char *p = new char[10];
    foo(p);
    printf("p=%s\n", p);
    return 0;
}
