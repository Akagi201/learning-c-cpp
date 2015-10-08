#include <stdio.h>
#include <math.h>

// Kahan Sum
double kahan_sum(double *a, int length) {
    double sum = a[1];
    double c = 0.0, y, t;
    int i;

    for (i = 2; i < length; i++) {
        y = a[i] - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

// Naive Sum
double naive_sum(double *a, int length) {
    double sum = 0;
    for (int i = 1; i < length; i++) {
        sum += a[i];
    }

    return sum;
}

int main() {
    double table[10000] = {};
    table[0] = 1.0;
    for (int i = 1; i < 10000; i++) {
        table[i] = 1e-16;
    }
    printf("naive = %1.14e\n", naive_sum(table, 10000));
    printf("kahan = %1.14e\n", kahan_sum(table, 10000));

    return 0;
}
