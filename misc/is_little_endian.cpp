#include <iostream>
#include <stdint.h>
#include <stdio.h>

bool srs_is_little_endian() {
    // convert to network(big-endian) order, if not equals,
    // the system is little-endian, so need to convert the int64
    static int little_endian_check = -1;

    if (little_endian_check == -1) {
        union {
            int32_t i;
            int8_t c;
        } little_check_union;

        little_check_union.i = 0x01;
        little_endian_check = little_check_union.c;
    }

    return (little_endian_check == 1);
}

int main() {
    bool r = srs_is_little_endian();
    printf("srs_is_little_endian: %d\n", r);
}
