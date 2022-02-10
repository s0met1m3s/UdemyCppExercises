#include <cstdint>
#include <iostream>

void print_array(const std::int32_t *array, const std::size_t length);

void print_array(const char *array);

int main()
{
    const std::int32_t array[]{1, 2, 3};
    const char String[]{"Jan"};

    print_array(array, 3);
    print_array(String);

    return 0;
}

void print_array(const std::int32_t *array, const std::size_t length)
{
    if (array == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < length - 1; i++)
    {
        std::cout << array[i] << ", ";
    }

    std::cout << array[length - 1] << '\n';
}

void print_array(const char *array)
{
    if (array == nullptr)
    {
        return;
    }

    while (*array != '\0')
    {
        std::cout << *array;
        array++;
    }

    std::cout << '\n';
}
