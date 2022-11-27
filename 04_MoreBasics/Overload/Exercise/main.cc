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
