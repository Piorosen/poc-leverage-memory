#include <code/args.h>
#include <iostream>
#include <cxxopts.hpp>

namespace args {
args parse_arguments(int argc, char* argv[]) {
    args arguments;

    try {
        cxxopts::Options options("MatrixTranspose", "A program to transpose matrices");

        options.add_options()
            ("v,verbose", "Enable verbose output", cxxopts::value<bool>()->default_value("false"))
            ("M", "Number of rows", cxxopts::value<int>())
            ("N", "Number of columns", cxxopts::value<int>())
            ("K", "Some additional parameter K", cxxopts::value<int>())
            ("o,output", "Output file", cxxopts::value<std::string>())
            ("h,help", "Print usage");

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            exit(0);
        }

        arguments.verbose = result["verbose"].as<bool>();
        arguments.M = result["M"].as<int>();
        arguments.N = result["N"].as<int>();
        arguments.K = result["K"].as<int>();
        arguments.output_file = result["output"].as<std::string>();

    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        exit(1);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }

    return arguments;
}
}