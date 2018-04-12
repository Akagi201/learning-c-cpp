#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "perfecthash.h"



int main(int argc, const char** argv) {

    for (int i=1; i<argc; i++) {
        const CommandOption* opt = Perfect_Hash::IsValidCommandLineOption(argv[i], strlen(argv[i]));
        if ( opt != NULL ) {
            fprintf(stderr, "ValidOption: %s, %d\n", opt->Option, opt->OptionCode);
        } else {
            fprintf(stderr, "InvalidOption: %s\n", argv[i]);
        }
    }
    return 0;
}
