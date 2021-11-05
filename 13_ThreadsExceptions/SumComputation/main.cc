#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <future>

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
    int i = 0;
    int n = static_cast<int>(vec.size());

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
    std::vector<int> my_vector(20'000'000, 0);
    random_vector(my_vector);

    double time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn(my_vector.begin(), my_vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Time1: " << time1 / NUM_RUNS << "ms Sum: " << sum1 << std::endl;

    double time2 = 0.0;
    volatile auto sum2 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t2;
        sum2 = std::accumulate(my_vector.begin(), my_vector.end(), 0);
        time2 += t2.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Time2: " << time2 / NUM_RUNS << "ms Sum: " << sum2 << std::endl;

    double time3 = 0.0;
    volatile auto sum3 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t3;
        sum3 = parallel_sum_omp(my_vector);
        time3 += t3.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Time3: " << time3 / NUM_RUNS << "ms Sum: " << sum3 << std::endl;

    auto sum4 = 0;
    auto length = my_vector.size();
    auto mid = my_vector.begin() + length / 2;
    double time4 = 0.0;
    cpptiming::Timer t4;
    std::thread t1(range_sum_thread<decltype(my_vector)::iterator>, my_vector.begin(), mid, std::ref(sum4));
    std::thread t2(range_sum_thread<decltype(my_vector)::iterator>, mid, my_vector.end(), std::ref(sum4));
    t1.join();
    t2.join();
    time4 += t4.elapsed_time<cpptiming::millisecs, double>();
    std::cout << "Mean Time3: " << time4 / 1 << "ms Sum: " << sum4 << std::endl;

    return 0;
}
