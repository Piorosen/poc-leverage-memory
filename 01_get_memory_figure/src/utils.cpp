#include <code/utils.h>
#include <assert.h>
#include <iostream>
#include <fstream>

namespace utils {
    std::vector<int> get_available_frequency(const int core_pin) {
        std::vector<int> result;
        char buffer[256];
        snprintf(buffer, 256, "%s%d%s", "/sys/devices/system/cpu/cpu", core_pin, "/cpufreq/scaling_available_frequencies");
        std::ifstream file(buffer, std::ios::in);
        int mem;
        while (!file.eof()) {
            file >> mem;
            result.push_back(mem);
        }
        file.close();
        return result;
    }

    void set_cpu_frequency(const int core_pin, const int freq) {
        char buffer[256];
        snprintf(buffer,256, "%s%d%s", "/sys/devices/system/cpu/cpu", core_pin, "/cpufreq/scaling_setspeed");
        std::ofstream file(buffer, std::ios::out);
        file << freq;
        file.close();
    }

    std::vector<int> get_current_frequency(const int max_cpu) {
        int cpu_num = max_cpu;
        char buffer[256] { 0, };
        std::vector<int> result;
        for (int num = 0; num < cpu_num; num++) {
            snprintf(buffer, 256, "%s%d%s", "/sys/devices/system/cpu/cpu", num, "/cpufreq/scaling_cur_freq");
            std::ifstream file(buffer, std::ios::in);
            int mem;
            if (file.is_open()) {
                file >> mem;
            }
            result.push_back(mem);
        }
        return result;
    }

    std::vector<std::string> get_available_governors(const int core_pin) {
        char buffer[256];
        std::vector<std::string> result;
        snprintf(buffer, 256, "%s%d%s", "/sys/devices/system/cpu/cpu", core_pin, "/cpufreq/scaling_available_governors");
        std::ifstream file(buffer, std::ios::in);

        std::string data;
        while (!file.eof()) {
            file >> data;
            result.push_back(data);
        }
        return result;
    }

    void set_governors(const int core_pin, const std::string& governors) {
        char buffer[256];
        snprintf(buffer, 256, "%s%d%s", "/sys/devices/system/cpu/cpu", core_pin, "/cpufreq/scaling_governor");

        std::ofstream file(buffer, std::ios::out);
        file << governors;
        file.close();
    }

    std::string get_governors(const int core_pin) {
        char buffer[256];
        snprintf(buffer, 256, "%s%d%s", "/sys/devices/system/cpu/cpu", core_pin, "/cpufreq/scaling_governor");
        std::string result;
        std::ifstream file(buffer, std::ios::in);
        file >> result;
        file.close();
        return result;
    }

    bool set_thread_affinity(int core_id)
    {
        assert(core_id < 0);
#if !defined(_WIN64) && !defined(__APPLE__) && !defined(__OpenBSD__)
        cpu_set_t set;
        CPU_ZERO(&set);
        CPU_SET(core_id, &set);
        sched_setaffinity(0, sizeof(set), &set);
        return true;
#endif
        return false;
    }

    std::vector<cluster> partition_core_freq(int core_count, bool verbose)
    {
        std::vector<cluster> result;

        std::vector<int> freq_tmp;
        cluster c;
        for (int i = 0; i < core_count; i++) {
            auto freq = get_available_frequency(i);
            c.frequency = freq_tmp;
            if (freq == freq_tmp || freq_tmp.empty()) {
                c.core.push_back(i);
            }else {
                result.push_back(c);
                c.core.clear();
                c.frequency.clear();
            }
            freq_tmp = freq;
        }

        if (!c.core.empty() || !c.frequency.empty()) {
            result.push_back(c);
        }

        if (verbose) {
            printf("\n");
            for (int i = 0; i < result.size() ; i++) {
                printf("[%02d] : ", i);
                for (int c = 0; c < result[i].core.size(); c++) {
                    printf("%d, ", result[i].core[c]);
                }
                printf("\n");
            }
        }

        return result;
    }

    void setup(int core, bool verbose)
    {
        printf("%d   ]]]\n", core);
        int cpu_core = core;

        auto cf = partition_core_freq(cpu_core, verbose);
        for (int i = 0; i < cf.size(); i++)
        {
            for (const auto &core : cf[i].core)
            {
                set_governors(core, "userspace");
                set_cpu_frequency(core, cf[i].frequency.back());
            }
        }

        auto cur_freq = get_current_frequency(cpu_core);
        std::cout << "Available Governors\n";
        for (int i = 0; i < cpu_core; i++)
        {
            auto freq = get_available_frequency(i);
            auto gov = get_available_governors(i);
            auto cur_gov = get_governors(i);
            std::cout << "Core Pin : [ " << i + 1 << " ] \n";
            std::cout << "Current Freq : [ " << cur_freq[i] << " ] \n";
            std::cout << "Current Gov : [ " << cur_gov << " ] \n";
            std::cout << "Available Freq : [ ";
            for (const auto &data : freq)
            {
                std::cout << data << ", ";
            }
            std::cout << "]\n";

            std::cout << "Available Governors : [ ";
            for (const auto &data : gov)
            {
                std::cout << data << ", ";
            }
            std::cout << "]\n\n\n";
        }

        return;
    }

    void remove_cache() {
        system("sync; echo 3 > /proc/sys/vm/drop_caches");
    }
}
