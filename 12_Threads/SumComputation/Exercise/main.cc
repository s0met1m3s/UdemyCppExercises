#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Timer.hpp"
#include "utils.hpp"

constexpr static std::uint32_t NUM_ELEMENTS = 30'000'000;
constexpr static std::uint32_t ELEMENTS_THRESHOLD = 5'000'000;
constexpr static std::uint32_t NUM_RUNS = 1'000;

template <typename T, typename RandomIter>
T range_sum_asyn(RandomIter start, RandomIter stop);

int main()
{
    std::vector<std::int32_t> vector(NUM_ELEMENTS, 0);
    random_vector(vector);

    auto time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn<std::int32_t>(vector.begin(), vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1
              << '\n';

    return 0;
}
