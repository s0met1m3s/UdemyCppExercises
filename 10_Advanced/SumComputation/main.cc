#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

#include "omp.h"
#include <Timer.hpp>

constexpr std::uint32_t NUM_THREADS = 4;
constexpr std::uint32_t NUM_RUNS = 100;

void random_vector(std::vector<int> &vec)
{
    std::mt19937 random_generator(42);
    std::uniform_int_distribution<int> random_distribution(-10, 10);

    for (auto &val : vec)
    {
        val = random_distribution(random_generator);
    }
}

int parallel_sum_omp(std::vector<int> &vec)
{
    int final_sum = 0;
    int sum = 0;
    unsigned int i = 0;
    unsigned int n = static_cast<unsigned int>(vec.size());

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

    int sum = range_sum_asyn(start, mid);
    return sum + handle.get();
}

template <typename RandomIter>
void range_sum_thread(RandomIter start, RandomIter stop, int &sum)
{
    sum += std::accumulate(start, stop, 0);
}

int main()
{
    std::vector<int> my_vector(30'000'000, 0);
    random_vector(my_vector);

    double time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn(my_vector.begin(), my_vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1 << std::endl;

    double time2 = 0.0;
    volatile auto sum2 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t2;
        sum2 = std::accumulate(my_vector.begin(), my_vector.end(), 0);
        time2 += t2.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Serial: " << time2 / NUM_RUNS << "ms sum: " << sum2 << std::endl;

    double time3 = 0.0;
    volatile auto sum3 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t3;
        sum3 = parallel_sum_omp(my_vector);
        time3 += t3.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean OpenMP: " << time3 / NUM_RUNS << "ms sum: " << sum3 << std::endl;

    auto sum4 = 0;
    auto length = my_vector.size();
    auto quarter = static_cast<long>(length) / 4L;
    auto half = static_cast<long>(length) / 2L;
    auto split1 = my_vector.begin() + quarter;
    auto split2 = my_vector.begin() + half;
    auto split3 = my_vector.begin() + half + quarter;
    double time4 = 0.0;
    cpptiming::Timer t4;
    std::thread thread1(range_sum_thread<decltype(my_vector)::iterator>,
                        my_vector.begin(),
                        split1,
                        std::ref(sum4));
    std::thread thread2(range_sum_thread<decltype(my_vector)::iterator>,
                        split1,
                        split2,
                        std::ref(sum4));
    std::thread thread3(range_sum_thread<decltype(my_vector)::iterator>,
                        split2,
                        split3,
                        std::ref(sum4));
    std::thread thread4(range_sum_thread<decltype(my_vector)::iterator>,
                        split3,
                        my_vector.end(),
                        std::ref(sum4));
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    time4 += t4.elapsed_time<cpptiming::millisecs, double>();
    std::cout << "Mean Threadding: " << time4 / 1 << "ms sum: " << sum4 << std::endl;

    return 0;
}
