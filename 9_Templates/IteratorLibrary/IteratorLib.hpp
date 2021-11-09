#include <cstdint>
#include <iterator>
#include <list>

namespace mystd
{

template <typename FwIt>
void advance(FwIt &it, typename std::iterator_traits<FwIt>::difference_type n)
{
    auto dist = typename std::iterator_traits<FwIt>::difference_type(n);

    while (dist > 0)
    {
        --dist;
        ++it;
    }
}

template <typename FwIt>
typename std::iterator_traits<FwIt>::difference_type distance(FwIt first, FwIt last)
{
    typename std::iterator_traits<FwIt>::difference_type result = 0;

    while (first != last)
    {
        ++first;
        ++result;
    }

    return result;
}

template <typename FwIt>
FwIt next(FwIt it, typename std::iterator_traits<FwIt>::difference_type n = 1)
{
    mystd::advance(it, n);
    return it;
}

template <typename BiIt>
BiIt prev(BiIt it, typename std::iterator_traits<BiIt>::difference_type n = 1)
{
    mystd::advance(it, -n);
    return it;
}

} // namespace mystd
