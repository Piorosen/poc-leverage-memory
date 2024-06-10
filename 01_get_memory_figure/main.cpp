#include <iostream>
#include <array>

#include <code/compute.h>

using namespace compute;

constexpr size_t M = 2048;
static array<array<float, M>, M> A;
static decltype(A) B;
static decltype(A) C;

int main(int argc, char** argv) {
    float a, b;
    a = 1, b = 0;
    cout << "time : " << perform<milliseconds>(gemm<float, M>, A, B, C, a, b) << "\n";
    return 0;
}

