#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

template <typename T> void printArray(const T *const Array, const std::size_t Length)
{
    for (std::size_t i = 0; i < Length - 1; i++)
    {
        std::cout << Array[i] << ", ";
    }

    std::cout << Array[Length - 1] << std::endl;
}

template <typename T> void printVector(const std::vector<T> Vector)
{
    for (std::size_t i = 0; i < Vector.size() - 1; i++)
    {
        std::cout << Vector[i] << ", ";
    }

    std::cout << Vector[Vector.size() - 1] << std::endl;
}

#endif /* UTILS_H */
