#include <iostream>
#include <cstdlib>

#include "cmdline.h"

int main(int argc, char *argv[]) {
    gengetopt_args_info ai;
    if (cmdline_parser(argc, argv, &ai) != 0) {
        exit(1);
    }

    std::cout << ai.filename_arg << std::endl;

    if (ai.size_given) {
        std::cout << ai.size_arg[0] << " "
        << ai.size_arg[1] << " "
        << ai.size_arg[2] << std::endl;
    }

    for (int i = 0; i < ai.array_given; ++i) {
        std::cout << ai.array_arg[i] << " ";
    }
    std::cout << std::endl;

    if (ai.long_option_given) {
        std::cout << ai.long_option_arg << std::endl;
    }

    std::cout << ai.default_value_arg << std::endl;
    std::cout << ai.console_flag << std::endl;

    return 0;
}
