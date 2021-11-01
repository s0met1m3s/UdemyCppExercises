#include <cstring>
#include <iostream>
#include <vector>

#include "utils.h"

void uniqueElements(std::vector<int> &);
void removeDuplicates(std::vector<int> &);
void rotateLeft(std::vector<int> &);
void rotateRight(std::vector<int> &);

void swapBoundaryValues(std::vector<int> &);

int main()
{
    auto Vector = std::vector<int>{1, 1, 2, 3, 3, 4};

    std::cout << "uniqueElements: " << std::endl;
    uniqueElements(Vector);

    std::cout << "removeDuplicates: " << std::endl;
    removeDuplicates(Vector);
    printVector(Vector);

    std::cout << "rotateLeft: " << std::endl;
    rotateLeft(Vector);
    printVector(Vector);

    std::cout << "rotateRight: " << std::endl;
    rotateRight(Vector);
    printVector(Vector);

    return 0;
}

void uniqueElements(std::vector<int> &Vector)
{
    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        auto unique = true;
        auto CurrentValue = Vector[i];

        for (std::size_t j = 0; j < Vector.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (CurrentValue == Vector[j])
            {
                unique = false;
            }
        }

        if (unique == true)
        {
            std::cout << "unique element: " << CurrentValue << std::endl;
        }
    }
}

void removeDuplicates(std::vector<int> &Vector)
{
    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        auto duplicateIndex = static_cast<std::size_t>(-1);
        auto CurrentValue = Vector[i];

        for (std::size_t j = i + 1; j < Vector.size(); j++)
        {
            if (CurrentValue == Vector[j])
            {
                duplicateIndex = j;
                Vector.pop_back();
                break;
            }
        }

        if (duplicateIndex == static_cast<std::size_t>(-1))
        {
            continue;
        }

        for (std::size_t j = duplicateIndex; j < Vector.size(); j++)
        {
            Vector[j] = Vector[j + 1];
        }

        Vector[Vector.size()] = 0;
    }
}

void rotateLeft(std::vector<int> &Vector)
{
    auto FirstElement = Vector[0];

    for (std::size_t i = 1; i < Vector.size(); i++)
    {
        Vector[i - 1] = Vector[i];
    }

    Vector[Vector.size() - 1] = FirstElement;
}

void rotateRight(std::vector<int> &Vector)
{
    auto LastElement = Vector[Vector.size() - 1];

    for (std::size_t i = Vector.size() - 1; i > 0; i--)
    {
        Vector[i] = Vector[i - 1];
    }

    Vector[0] = LastElement;
}

void swapBoundaryValues(std::vector<int> &Vector)
{
    auto &FrontPointer = Vector.front();
    auto &BackPointer = Vector.back();

    const auto Temp = BackPointer;
    BackPointer = FrontPointer;
    FrontPointer = Temp;
}
