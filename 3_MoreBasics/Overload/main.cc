#include <iostream>

void print_array(const int *array, const std::size_t length);

void print_array(const char *array);

int main()
{
    int array[] = {1, 2, 3};
    char String[] = "Jan";

    print_array(array, 3);
    print_array(String);

    return 0;
}


void print_array(const int *array, const std::size_t length)
{
    for (std::size_t i = 0; i < length - 1; i++)
    {
        std::cout << array[i] << ", ";
    }

    std::cout << array[length - 1] << std::endl;
}

void print_array(const char *array)
{
    while (*array != '\0')
    {
        std::cout << *array;
        array++;
    }

    std::cout << std::endl;
}
