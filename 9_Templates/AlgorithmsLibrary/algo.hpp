#pragma once

namespace mystd
{

template <class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
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

template <class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size count, const T &value)
{
    for (Size i = 0; i < count; ++i)
    {
        *first++ = value;
    }
    return first;
}

template <class ForwardIter, class T>
void iota(ForwardIter first, ForwardIter last, T value)
{
    while (first != last)
    {
        *first++ = value;
        ++value;
    }
}

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

template <class InputIter, class T>
T accumulate(InputIter first, InputIter last, T init)
{
    for (; first != last; ++first)
    {
        init += *first;
    }
    return init;
}

} // namespace mystd
