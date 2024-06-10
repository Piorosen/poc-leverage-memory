#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

namespace memory {
// Size of the memory array
const int MEMORY_SIZE = 10000000;
// // Shared memory array for stress testing
float memory[MEMORY_SIZE];

// Function for memory read stress test
void memory_read_test(int thread_id, int reads_per_thread) {
    for (int i = 0; i < reads_per_thread; ++i) {
        int index = rand() % MEMORY_SIZE; // Random index within memory range
        float value = memory[index];
        // Perform some operation with the read value (optional)
        // For example, printing the value
        std::cout << "Thread " << thread_id << ": Read value at index " << index << " = " << value << std::endl;
    }
}

// Function for memory write stress test
void memory_write_test(int thread_id, int writes_per_thread) {
    for (int i = 0; i < writes_per_thread; ++i) {
        int index = rand() % MEMORY_SIZE; // Random index within memory range
        float value = static_cast<float>(thread_id); // Value to write (thread ID)
        memory[index] = value;
        // Perform some operation after writing (optional)
    }
}

int main() {
      // Seed the random number generator
    srand(static_cast<unsigned int>(std::time(nullptr)));

    // Number of threads to create
    const int num_threads = 4;
    // Number of reads and writes each thread should perform
    const int reads_per_thread = 1000000;
    const int writes_per_thread = 1000000;

    // Vector to hold thread objects
    std::vector<std::thread> threads;

    // Start the read threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(memory_read_test, i, reads_per_thread);
    }

    // Start the write threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(memory_write_test, i, writes_per_thread);
    }

    // Join the threads with the main thread
    for (auto& thread : threads) {
        thread.join();
    }
}

}

#endif
