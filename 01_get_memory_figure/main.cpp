#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include <code/args.h>
#include <code/utils.h>

// #include <code/compute.h>

constexpr int X = 4;
constexpr int Y = 8;
int main(int argc, char* argv[]) {
    auto arg = args::parse_arguments(argc, argv);
    if (arg.verbose) { 
        spdlog::info("Arguments : [{} : {}]", "M" , arg.M);
        spdlog::info("Arguments : [{} : {}]", "N" , arg.N);
        spdlog::info("Arguments : [{} : {}]", "K" , arg.K);
        spdlog::info("Arguments : [{} : {}]", "Verbose" , arg.verbose);
        spdlog::info("Arguments : [{} : {}]", "Output" , arg.output_file);
        spdlog::info("");
        spdlog::info("CORES : {}", utils::get_cpu_core_count());

        auto data = utils::partition_core_freq(utils::get_cpu_core_count());
        if (true) {
            spdlog::info("");
            for (int i = 0; i < data.size() ; i++) {
                spdlog::info("Cluster [{}]", i);
                spdlog::info("Core : {}", fmt::join(data[i].core, ", "));
                spdlog::info("Frequency : {}", fmt::join(data[i].frequency, ", "));
                spdlog::info("");
            }
        }
    }
    
    
    // float* A, *B;
    // A = (float*)malloc(X * Y * sizeof(float));
    // B = (float*)malloc(Y * X * sizeof(float));
    // random(Y, X, A);
    // cout << perform<milliseconds>(transpose<float>, Y, X, A, B).count() << " ms\n";
    // print(Y, X, A);
    // cout << "\n\n";
    // print(X, Y, B);
    return 0;
}

