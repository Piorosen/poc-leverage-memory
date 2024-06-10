#ifndef ARGS_H
#define ARGS_H

#include <string>

namespace args {
    struct args {
        int repeat;
        int M, N, K;
        std::string output_file;
        bool verbose;
    };

    args parse_arguments(int argc, char* argv[]);
}

#endif
