# Exercise

Note: Based on Chapter 13 in the main course.

```cpp
#include "utils.hpp"
#include "Timer.hpp"

template <typename RandomIter>
auto range_sum_asyn(RandomIter start, RandomIter stop)
```

Implement an async function that computes the sum of a container in the range of the **start** and **stop** iterator.  
The function should launch several tasks within an async context.

E.g.

```cpp
std::async(std::launch::async, range_sum_asyn<RandomIter>, mid, stop);
```

## Main Function

```cpp
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "Timer.hpp"
#include "utils.hpp"

constexpr std::uint32_t NUM_RUNS = 1'000;

template <typename T, typename RandomIter>
T range_sum_asyn(RandomIter start, RandomIter stop)
{
    // ...
}

int main()
{
    std::vector<std::int32_t> vector(30'000'000, 0);
    random_vector(vector);

    auto time1 = 0.0;
    volatile auto sum1 = 0;
    for (std::uint32_t i = 0; i < NUM_RUNS; ++i)
    {
        cpptiming::Timer t1;
        sum1 = range_sum_asyn<std::int32_t>(vector.begin(), vector.end());
        time1 += t1.elapsed_time<cpptiming::millisecs, double>();
    }
    std::cout << "Mean Async: " << time1 / NUM_RUNS << "ms sum: " << sum1 << '\n';

    return 0;
}
```
