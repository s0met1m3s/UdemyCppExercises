#include "Lib.h"

namespace mystd
{
void advance(It &it, DifferenceType n)
{
    while (n > 0)
    {
        ++it;
        --n;
    }

    while (n < 0)
    {
        --it;
        ++n;
    }
}

DifferenceType distance(It first, It last)
{
    DifferenceType result = 0;

    while (first != last)
    {
        ++first;
        ++result;
    }

    return result;
}

It next(It it, DifferenceType n)
{
    mystd::advance(it, n);
    return it;
}

It prev(It it, DifferenceType n)
{
    mystd::advance(it, n);
    return it;
}
} // namespace my_str
