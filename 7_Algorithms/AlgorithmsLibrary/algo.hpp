#pragma once

#include <vector>

namespace mystd
{

bool equal(std::vector<int>::iterator first1,
           std::vector<int>::iterator last1,
           std::vector<int>::iterator first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }
    return true;
}

std::vector<int>::iterator fill_n(std::vector<int>::iterator first,
                                  std::size_t count,
                                  const int &value)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        *first++ = value;
    }
    return first;
}

void iota(std::vector<int>::iterator first, std::vector<int>::iterator last, int value)
{
    while (first != last)
    {
        *first++ = value;
        ++value;
    }
}

std::vector<int>::iterator copy(std::vector<int>::iterator first,
                                std::vector<int>::iterator last,
                                std::vector<int>::iterator d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

int accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last, int init)
{
    for (; first != last; ++first)
    {
        init += *first;
    }
    return init;
}

int inner_product(std::vector<int>::iterator first1,
                  std::vector<int>::iterator last1,
                  std::vector<int>::iterator first2,
                  int init)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        init = init + (*first1 * *first2);
    }
    return init;
}

} // namespace mystd
