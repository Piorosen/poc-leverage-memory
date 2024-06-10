//
// Created by ChaCha on 6/10/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils {
    using index = int;

    struct cluster {
        std::vector<int> frequency; // from per core information
        std::vector<index> core;
    };

#if !defined(_WIN64) && !defined(__APPLE__) && !defined(__OpenBSD__)
    std::vector<int> get_available_frequency(int core_pin);
    void set_cpu_frequency(int core_pin, int freq);

    std::vector<int> get_current_frequency(int max_cpu);
    std::vector<std::string> get_available_governors(int core_pin);

    void set_governors(int core_pin, std::string governors);
    std::string get_governors(int core_pin);

    bool set_thread_affinity(int core_id);
    std::vector<cluster> partition_core_freq(int core_count);

    void setup(int core_count, bool verbose);
    void remove_cache();
#endif
}


#endif //UTILS_H
