#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "utils.hpp"
#include <Timer.hpp>

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

void range_sum_thread_helper(std::vector<std::int32_t>::iterator start, std::vector<std::int32_t>::iterator stop)
{
    std::accumulate(start, stop, 0);
}

double range_sum_thread(const std::vector<std::int32_t> &vector)
{
    auto sum = 0;
    auto length = vector.size();
    auto quarter = static_cast<long>(length) / 2L;
    auto half = static_cast<long>(length) / 2L;
    auto split1 = vector.begin() + quarter;
    auto split2 = vector.begin() + half;
    auto split3 = vector.begin() + half + quarter;
    std::thread thread1(range_sum_thread_helper, vector.begin(), split1, std::ref(sum));
    std::thread thread2(range_sum_thread_helper, split1, split2, std::ref(sum));
    std::thread thread3(range_sum_thread_helper, split2, split3, std::ref(sum));
    std::thread thread4(range_sum_thread_helper, split3, vector.end(), std::ref(sum));
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return sum;
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

    double time2 = 0.0;
    cpptiming::Timer t2;
    auto sum2 = range_sum_thread(vector);
    time2 += t2.elapsed_time<cpptiming::millisecs, double>();
    std::cout << "Mean Threadding: " << time2 / 1 << "ms sum: " << sum2 << std::endl;

    return 0;
}
