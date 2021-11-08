#pragma once

#include <cstdint>
#include <vector>

namespace mystd
{

bool equal(std::vector<std::int32_t>::iterator first1,
           std::vector<std::int32_t>::iterator last1,
           std::vector<std::int32_t>::iterator first2);

std::vector<std::int32_t>::iterator fill_n(std::vector<std::int32_t>::iterator first,
                                           std::size_t count,
                                           const std::int32_t &value);

void iota(std::vector<std::int32_t>::iterator first, std::vector<std::int32_t>::iterator last, std::int32_t value);

std::vector<std::int32_t>::iterator copy(std::vector<std::int32_t>::iterator first,
                                         std::vector<std::int32_t>::iterator last,
                                         std::vector<std::int32_t>::iterator d_first);

std::int32_t accumulate(std::vector<std::int32_t>::iterator first,
                        std::vector<std::int32_t>::iterator last,
                        std::int32_t init);

} // namespace mystd
