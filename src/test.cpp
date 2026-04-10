#include <iostream>
#include "llama.h"
#include <chrono>
#include <omp.h>

int main() {
    const auto N = static_cast<size_t>(1e9);

    // --- Normal loop ---
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> result(N);
    for (size_t i = 0; i < N; i++) {
        result[i] = 2 * static_cast<int>(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    const double normal_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Normal loop: " << normal_ms << " ms\n";

    // --- OpenMP loop ---
    start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
        result[i] = 2 * static_cast<int>(i);
    }

    end = std::chrono::high_resolution_clock::now();
    const double omp_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "OpenMP loop: " << omp_ms << " ms\n";

    std::cout << "Speedup: " << normal_ms / omp_ms << "x\n";

    return 0;
}