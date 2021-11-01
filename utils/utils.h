#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <map>
#include <unordered_map>
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

void printVector(const std::vector<std::pair<std::string, std::size_t>> Vector)
{
    for (std::size_t i = 0; i < Vector.size() - 1; i++)
    {
        std::cout << Vector[i].first << ": " << Vector[i].second << ", ";
    }

    std::cout << Vector[Vector.size() - 1].first << ": " << Vector[Vector.size() - 1].second
              << std::endl;
}

template <typename T, typename U> void printMap(const std::map<T, U> Map)
{
    for (const auto &[Key, Value] : Map)
    {
        std::cout << Key << ": " << Value << std::endl;
    }
}

template <typename T, typename U> void printMap(const std::unordered_map<T, U> Map)
{
    for (const auto &[Key, Value] : Map)
    {
        std::cout << Key << ": " << Value << std::endl;
    }
}

#endif /* UTILS_H */
