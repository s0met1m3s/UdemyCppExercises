#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Timer.hpp"
#include "utils.hpp"

constexpr std::uint32_t NUM_THREADS = 2;
constexpr std::uint32_t NUM_RUNS = 100;

template <typename RandomIter>
auto range_sum_asyn(RandomIter start, RandomIter stop)
{
    auto length = std::distance(start, stop);
    if (length < 1'000'000)
    {
        return std::accumulate(start, stop, 0);
    }

    RandomIter mid = start + length / 2;

    auto handle = std::async(std::launch::async, range_sum_asyn<RandomIter>, mid, stop);

    std::int32_t sum = range_sum_asyn<RandomIter>(start, mid);

    return sum + handle.get();
}

int main()
{
    std::vector<std::int32_t> vector(30'000'000, 0);
    random_vector(vector);

    double time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn(vector.begin(), vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1 << std::endl;

    return 0;
}
