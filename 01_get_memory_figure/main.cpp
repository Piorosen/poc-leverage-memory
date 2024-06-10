#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include <code/args.h>
#include <code/utils.h>
#include <code/compute.h>

using namespace std;
using namespace std::chrono;

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
    
    float* A, *B;
    A = (float*)malloc(arg.M * arg.K * sizeof(float));
    B = (float*)malloc(arg.K * arg.N * sizeof(float));
    compute::random(arg.M, arg.K, A);
    compute::print(arg.M, arg.K, A);
    cout << compute::perform<milliseconds>(compute::transpose<float>, arg.M, arg.K, A, B).count() << " ms\n";
    cout << compute::perform<milliseconds>(compute::transpose<float>, arg.M, arg.K, B, A).count() << " ms\n";
    cout << "\n\n";
    compute::print(arg.M, arg.K, A);
    return 0;
}

