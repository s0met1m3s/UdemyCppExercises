# Exercise

Implement the following functions:

```cpp
void unique_elements(std::int32_t *array, std::size_t length);

void remove_duplicates(std::int32_t *array, std::size_t &length);

void rotate_left(std::int32_t *array, std::size_t length);

void rotate_right(std::int32_t *array, std::size_t length);
```

## Main Function

```cpp
int main()
{
    std::int32_t array[]{1, 1, 2, 3, 3, 4};
    std::size_t length = 6;

    std::cout << "unique_elements: " << std::endl;
    unique_elements(array, length);

    remove_duplicates(array, length);
    print_array(array, length);

    rotate_left(array, length);
    print_array(array, length);

    rotate_right(array, length);
    print_array(array, length);

    return 0;
}
```
