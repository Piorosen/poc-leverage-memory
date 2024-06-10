//
// Created by ChaCha on 6/10/24.
//

#ifndef COMPUTE_H
#define COMPUTE_H

#include <chrono>
#include <array>

using namespace std;
using namespace std::chrono;


namespace compute {

    template<typename TIME, typename CALLBACK, typename... ARGS>
    decltype(auto) perform(const CALLBACK& func, ARGS&... args) {
        auto start = high_resolution_clock::now();
        func(args...);
        auto end = high_resolution_clock::now();
        return duration_cast<TIME>(end - start);
    }

    template<typename T, size_t M, size_t N>
    void transpose(const array<array<T, M>, N>& source,
                    array<array<T, N>, M>& target) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                target[j][i] = source[i][j];
            }
        }
    }

    template<typename T, size_t M, size_t N = M, size_t K = N>
    void gemm(const array<array<T, M>, K>& A,
              const array<array<T, K>, N>& B,
              array<array<T, M>, N> & C,
              T alpha = 1, T beta = 0) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                T sum = 0;
                for (size_t k = 0; k < K; ++k) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = alpha * sum + beta * C[i][j];
            }
        }
    }
}

#endif //COMPUTE_H
