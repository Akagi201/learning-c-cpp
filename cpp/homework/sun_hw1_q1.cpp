#include <stdio.h>
#include <math.h>

void get_binary(double x, int *b, int m) {
    double c = x;
    for (int i = 0; i < m; i++) {
        b[i] = floor(2 * c);
        c = 2 * c - b[i];
    }
}

int main() {
    int b[30] = {};
    get_binary(0.1, b, 30);

    for (int i = 0; i < 30; i++) {
        printf("%d", b[i]);
    }

    printf("\n");

    return 0;
}
