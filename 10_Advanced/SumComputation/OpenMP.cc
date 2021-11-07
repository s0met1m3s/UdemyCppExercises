#include <algorithm>
#include <assert.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "omp.h"

constexpr std::uint32_t NUM_THREADS = 8;
constexpr std::uint32_t NUM_RUNS = 100;

std::int64_t serial_sum(std::vector<std::int32_t> &vec)
{
    std::int64_t sum = 0;
    std::int32_t n = static_cast<std::int32_t>(vec.size());

    for (std::int32_t i = 0; i != n; ++i)
    {
        sum = sum + vec[i];
    }

    return sum;
}

std::int64_t parallel_sum_omp(std::vector<std::int32_t> &vec)
{
    std::int64_t final_sum = 0;
    std::int64_t sum = 0;
    std::int32_t i = 0;
    std::int32_t n = static_cast<std::int32_t>(vec.size());

#pragma omp parallel for reduction(+ : sum) num_threads(NUM_THREADS)
    for (i = 0; i < n; ++i)
    {
        sum = sum + vec[i];
    }
#pragma omp critical
    {
        final_sum += sum;
    }

    return final_sum;
}

/*
   Serial time in ms: 2.70182
2: OpenMP time in ms: 1.75645
4: OpenMP time in ms: 1.77568
6: OpenMP time in ms: 1.55757
8: OpenMP time in ms: 1.48456
*/
int _main()
{
    // SETUP
    constexpr std::uint32_t seed = 42;
    constexpr std::int64_t expected_sum = -5570;
    std::int64_t sum_vector = 0L;

    std::mt19937 gen(seed);
    std::uniform_int_distribution<std::int32_t> dist(-10, 10);
    std::vector<std::int32_t> vector_a(10'000'000, 0);
    std::generate(vector_a.begin(), vector_a.end(), [&]() { return dist(gen); });

    // SERIELL
    auto start = std::chrono::high_resolution_clock::now();
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        sum_vector = serial_sum(vector_a);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << std::endl << "Serial time in ms: " << ms.count() / NUM_RUNS;
    std::cout << std::endl
              << "Serial Sum: " << sum_vector << " Expected Sum: " << expected_sum << std::endl;
    assert(expected_sum == sum_vector);

    // OPENMP
    start = std::chrono::high_resolution_clock::now();
    for (std::int32_t i = 0; i < NUM_RUNS; ++i)
    {
        sum_vector = parallel_sum_omp(vector_a);
    }
    end = std::chrono::high_resolution_clock::now();
    ms = end - start;
    std::cout << std::endl << "OpenMP time in ms: " << ms.count() / NUM_RUNS;
    std::cout << std::endl
              << "Serial Sum: " << sum_vector << " Expected Sum: " << expected_sum << std::endl;
    assert(expected_sum == sum_vector);

    return 0;
}
