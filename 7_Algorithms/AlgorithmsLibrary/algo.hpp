#pragma once

#include <cstdint>
#include <vector>

namespace mystd
{

bool equal(std::vector<std::int32_t>::iterator first1,
           std::vector<std::int32_t>::iterator last1,
           std::vector<std::int32_t>::iterator first2)
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

std::vector<std::int32_t>::iterator fill_n(std::vector<std::int32_t>::iterator first,
                                           std::size_t count,
                                           const std::int32_t &value)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        *first++ = value;
    }
    return first;
}

void iota(std::vector<std::int32_t>::iterator first,
          std::vector<std::int32_t>::iterator last,
          std::int32_t value)
{
    while (first != last)
    {
        *first++ = value;
        ++value;
    }
}

std::vector<std::int32_t>::iterator copy(std::vector<std::int32_t>::iterator first,
                                         std::vector<std::int32_t>::iterator last,
                                         std::vector<std::int32_t>::iterator d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

std::int32_t accumulate(std::vector<std::int32_t>::iterator first,
                        std::vector<std::int32_t>::iterator last,
                        std::int32_t init)
{
    for (; first != last; ++first)
    {
        init += *first;
    }
    return init;
}

std::int32_t inner_product(std::vector<std::int32_t>::iterator first1,
                           std::vector<std::int32_t>::iterator last1,
                           std::vector<std::int32_t>::iterator first2,
                           std::int32_t init)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        init = init + (*first1 * *first2);
    }
    return init;
}

} // namespace mystd
