# Exercise

Implement the following functions:

```cpp
bool equal(std::vector<std::int32_t>::iterator first1,
           std::vector<std::int32_t>::iterator last1,
           std::vector<std::int32_t>::iterator first2);

std::vector<std::int32_t>::iterator fill_n(std::vector<std::int32_t>::iterator first,
                                           std::size_t count,
                                           const std::int32_t &value);

void iota(std::vector<std::int32_t>::iterator first,
          std::vector<std::int32_t>::iterator last,
          std::int32_t value);

std::vector<std::int32_t>::iterator copy(std::vector<std::int32_t>::iterator first,
                                         std::vector<std::int32_t>::iterator last,
                                         std::vector<std::int32_t>::iterator d_first);

std::int32_t accumulate(std::vector<std::int32_t>::iterator first,
                        std::vector<std::int32_t>::iterator last,
                        std::int32_t init);
```

- equal: Return true if all elements of both vectors are the same
- fill_n: Fill the vector **n** times with the value **value** within the range $[first, last)$
- iota: Fill the vector with incrementing the value **value** within the range $[first, last)$
- copy: Copy the elements from one vector to the other vector
- accumulate: Compute the sum of the vecotr within the range $[first, last)$

## Main Function

```cpp
int main()
{
    auto vec1 = std::vector<std::int32_t>(5, 0);
    auto vec2 = std::vector<std::int32_t>(5, 0);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    mystd::fill_n(vec1.begin(), 5, 1);
    print_vector(vec1);

    mystd::iota(vec2.begin(), vec2.end(), 0);
    print_vector(vec2);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    mystd::copy(vec2.begin(), vec2.end(), vec1.begin());

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    const auto sum = mystd::accumulate(vec1.begin(), vec1.end(), 0);
    std::cout << sum << std::endl;

    return 0;
}
```
