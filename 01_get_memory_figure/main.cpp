#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

#include <code/args.h>
#include <code/utils.h>
#include <code/compute.h>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    spdlog::info("Build Time : {}, {}", __TIME__, __DATE__);
#ifdef NDEBUG
    spdlog::info("This is a Release build");
#else
    spdlog::info("This is a Debug build");
#endif

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
    for (int i = 0; i < arg.repeat; i++) { 
        float* A = (float*)malloc(arg.M * arg.K * sizeof(float));
        float* B = (float*)malloc(arg.K * arg.N * sizeof(float));
        float* C = (float*)malloc(arg.M * arg.N * sizeof(float));

        compute::random(arg.M, arg.K, A);
        compute::random(arg.K, arg.N, B);
        cout << compute::perform<milliseconds>(compute::gemm<float>, arg.M, arg.N, arg.K, A, B, C, 1, 0).count() << " ms\n";
        
        free(A);
        free(B);
        free(C);
    }
    
}

