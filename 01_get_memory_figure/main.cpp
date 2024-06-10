#include <iostream>
#include <chrono>
#include <array>
#include "utils.h"

using namespace std;
using namespace std::chrono;

template<typename T, size_t SIZE = 1, size_t SEED = __TIME_UNIX__>
constexpr array<int, SIZE> get_random() {
    array<T, SIZE> data;
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    const unsigned int m = 0xFFFFFFFF; //2^32
    int current = SEED;
    for (int i = 0; i < SIZE; ++i) {
        current = (a * current + c) % m;
        data[i] = current;
    }
    return data;
}

constexpr auto p = get_random<int, 1000000>();

int main(int argc, char** argv) {
    auto s = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(high_resolution_clock::now() - s).count() << "\n";
    return 0;
}

