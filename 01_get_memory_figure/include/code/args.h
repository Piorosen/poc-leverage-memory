#ifndef ARGS_H
#define ARGS_H

#include <string>

namespace args {
    struct args {
        bool verbose;
        int M, N, K;
        std::string output_file;
    };

    args parse_arguments(int argc, char* argv[]);
}

#endif
