//
// Created by Arthur Gilfanov on 4/12/26.
//

#include "Math.h"
#include "../omp_config.h"
#include <cmath>
#include <omp.h>


float Math::random_float() {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

int Math::random_ind(const int sz) {
    return static_cast<int>(random_float() * sz);
}

/* Both of the softmaxes modify the vector in place*/
void Math::softmax(std::vector<float>& vec) {
    const size_t n = vec.size();
    float* data = vec.data();

    float max_val = data[0];
    for (int i = 1; i < n; i++) {
        max_val = std::max(max_val, data[i]);
    }

    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        data[i] = std::exp(data[i] - max_val);
        sum += data[i];
    }

    for (int i = 0; i < n; i++) {
        data[i] /= sum;
    }
}

void Math::parallel_softmax(std::vector<float>& vec) {
    if (vec.size() <= 1) return;

    if (vec.size() < OMP_PARALLEL_THRESHOLD) {
        softmax(vec);
        return;
    }

    const size_t n = vec.size();
    float* data = vec.data();

    /* Find the max value so that exp values do not get too big */
    float max_val = data[0];
    #pragma omp parallel
    {
        float curr_max = max_val;
        #pragma omp for nowait
        for (int i = 1; i < n; i++) {
            curr_max = std::max(curr_max, data[i]);
        }

        #pragma omp critical
        max_val = std::max(max_val, curr_max);

    }
    for (int i = 1; i < n; i++) {
        max_val = std::max(max_val, data[i]);
    }

    /* Subtract max just so exp values are not too big and exponentiate */
    #pragma omp parallel for simd
    for (int i = 0; i < n; i++) {
        data[i] = std::exp(data[i] - max_val);
    }

    float sum = 0.0f;
    #pragma omp parallel for simd reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }

    /* Normalize to get probabilities */
    #pragma omp parallel for simd
    for (int i = 0; i < n; i++) {
        data[i] /= sum;
    }
}