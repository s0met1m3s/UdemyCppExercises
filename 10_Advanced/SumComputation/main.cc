#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

#include <Timer.hpp>

constexpr std::uint32_t NUM_THREADS = 2;
constexpr std::uint32_t NUM_RUNS = 100;

void random_vector(std::vector<std::int32_t> &vec)
{
    std::mt19937 random_generator(22);
    std::uniform_int_distribution<std::int32_t> random_distribution(-10, 10);

    for (auto &val : vec)
    {
        val = random_distribution(random_generator);
    }
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

    std::int32_t sum = range_sum_asyn(start, mid);
    return sum + handle.get();
}

template <typename RandomIter>
void range_sum_thread_helper(RandomIter start, RandomIter stop, std::int32_t &sum)
{
    sum += std::accumulate(start, stop, 0);
}

double range_sum_thread(const std::vector<std::int32_t> &my_vector)
{
    auto sum = 0;
    auto length = my_vector.size();
    auto quarter = static_cast<long>(length) / 2L;
    auto half = static_cast<long>(length) / 2L;
    auto split1 = my_vector.begin() + quarter;
    auto split2 = my_vector.begin() + half;
    auto split3 = my_vector.begin() + half + quarter;
    std::thread thread1(range_sum_thread_helper<std::vector<std::int32_t>::iterator>,
                        my_vector.begin(),
                        split1,
                        std::ref(sum));
    std::thread thread2(range_sum_thread_helper<std::vector<std::int32_t>::iterator>,
                        split1,
                        split2,
                        std::ref(sum));
    std::thread thread3(range_sum_thread_helper<std::vector<std::int32_t>::iterator>,
                        split2,
                        split3,
                        std::ref(sum));
    std::thread thread4(range_sum_thread_helper<std::vector<std::int32_t>::iterator>,
                        split3,
                        my_vector.end(),
                        std::ref(sum));
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return sum;
}

int main()
{
    std::vector<std::int32_t> my_vector(30'000'000, 0);
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
    cpptiming::Timer t2;
    auto sum2 = range_sum_thread(my_vector);
    time2 += t2.elapsed_time<cpptiming::millisecs, double>();
    std::cout << "Mean Threadding: " << time2 / 1 << "ms sum: " << sum2 << std::endl;

    return 0;
}
