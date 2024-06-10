//
// Created by ChaCha on 6/10/24.
//

#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

namespace compute {

    template<typename TIME, typename CALLBACK, typename... ARGS>
    decltype(auto) perform(const CALLBACK& func, ARGS... args) {
        auto start = high_resolution_clock::now();
        func(args...);
        auto end = high_resolution_clock::now();
        return duration_cast<TIME>(end - start);
    }

    template<typename T> // 8, 4 -> 4, 8
    void transpose(size_t M, size_t N, 
                    const T* source, T* target) {
        for (size_t j = 0; j < N; ++j) {
            for (size_t i = 0; i < M; ++i) {
                target[j * M + i] = source[i * N + j];
            }
        }
    }

    template<typename T>
    void gemm(size_t M, size_t N, size_t K,
              const T* A, const T* B, T* C,
              T alpha = 1, T beta = 0) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                T sum = 0;
                for (size_t k = 0; k < K; ++k) {
                    sum += A[i * N + k] * B[k * N + j];
                }
                C[i * N + j] = alpha * sum + beta * C[i * N + j];
            }
        }
    }
    template<typename T>
    void random(size_t M, size_t N, T* A) {
        random_device rd;
        uniform_real_distribution<T> ufm(0, 9.9);
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                A[i * N + j] = ufm(rd);
            }
        }
     }
    
    template<typename T>
    void print(size_t M, size_t N, const T* A) {
        cout<<fixed;

        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                cout.precision(3);
                cout << A[i * N + j] << '\t';
            }
            cout << '\n';
        }
    }
       // template<typename T, size_t M, size_t N>
    // void transpose(const array<array<T, M>, N>& source,
    //                 array<array<T, N>, M>& target) {
    //     for (size_t i = 0; i < M; ++i) {
    //         for (size_t j = 0; j < N; ++j) {
    //             target[j][i] = source[i][j];
    //         }
    //     }
    // }
    // template<typename T, size_t M, size_t N = M, size_t K = N>
    // void gemm(const array<array<T, M>, K>& A,
    //           const array<array<T, K>, N>& B,
    //           array<array<T, M>, N> & C,
    //           T alpha = 1, T beta = 0) {
    //     for (size_t i = 0; i < M; ++i) {
    //         for (size_t j = 0; j < N; ++j) {
    //             T sum = 0;
    //             for (size_t k = 0; k < K; ++k) {
    //                 sum += A[i][k] * B[k][j];
    //             }
    //             C[i][j] = alpha * sum + beta * C[i][j];
    //         }
    //     }
    // }
}

#endif //COMPUTE_H
