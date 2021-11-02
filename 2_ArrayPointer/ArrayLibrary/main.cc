#include <cstring>
#include <iostream>

#include "utils.h"

void uniqueElements(int *Array, std::size_t Length);
void removeDuplicates(int *Array, std::size_t &Length);
void rotateLeft(int *Array, std::size_t Length);
void rotateRight(int *Array, std::size_t Length);

int main()
{
    int Array[] = {1, 1, 2, 3, 3, 4};
    std::size_t Length = 6;

    std::cout << "uniqueElements: " << std::endl;
    uniqueElements(Array, Length);

    removeDuplicates(Array, Length);
    printArray(Array, Length);

    rotateLeft(Array, Length);
    printArray(Array, Length);

    rotateRight(Array, Length);
    printArray(Array, Length);

    return 0;
}

void uniqueElements(int *Array, std::size_t Length)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        bool unique = true;
        int CurrentValue = Array[i];

        for (std::size_t j = 0; j < Length; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (CurrentValue == Array[j])
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

void removeDuplicates(int *Array, std::size_t &Length)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        std::size_t duplicateIndex = std::string::npos;
        int CurrentValue = Array[i];

        for (std::size_t j = i + 1; j < Length; j++)
        {
            if (CurrentValue == Array[j])
            {
                duplicateIndex = j;
                Length--;
                break;
            }
        }

        if (duplicateIndex == -1)
        {
            continue;
        }

        for (std::size_t j = duplicateIndex; j < Length; j++)
        {
            Array[j] = Array[j + 1];
        }

        Array[Length] = 0;
    }
}

void rotateLeft(int *Array, std::size_t Length)
{
    int FirstElement = Array[0];

    for (std::size_t i = 1; i < Length; i++)
    {
        Array[i - 1] = Array[i];
    }

    Array[Length - 1] = FirstElement;
}

void rotateRight(int *Array, std::size_t Length)
{
    int LastElement = Array[Length - 1];

    for (std::size_t i = Length - 1; i > 0; i--)
    {
        Array[i] = Array[i - 1];
    }

    Array[0] = LastElement;
}
