#include <iostream>

void printArray(const int *Array, const std::size_t Length);

void printArray(const char *Array);

int main()
{
    int Array[] = {1, 2, 3};
    char String[] = "Jan";

    printArray(Array, 3);
    printArray(String);

    return 0;
}


void printArray(const int *Array, const std::size_t Length)
{
    for (std::size_t i = 0; i < Length - 1; i++)
    {
        std::cout << Array[i] << ", ";
    }

    std::cout << Array[Length - 1] << std::endl;
}

void printArray(const char *Array)
{
    while (*Array != '\0')
    {
        std::cout << *Array;
        Array++;
    }

    std::cout << std::endl;
}
