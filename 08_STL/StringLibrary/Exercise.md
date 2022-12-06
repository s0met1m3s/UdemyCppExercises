# Exercise

Implement the following functions:

```cpp
std::string to_upper_case(std::string_view text);

std::string to_lower_case(std::string_view text);

std::size_t string_length(std::string_view text);

bool string_equal(std::string_view string1, std::string_view string2);
```

Update the functions from chapter 2 regarding using string, string_view, and algorithms from the std.

## Main Function

```cpp
int main()
{
    auto in_text = std::string{};
    const auto compare_text1 = std::string{"jan"};
    const auto compare_text2 = std::string{"ja"};

    std::cout << "Please enter any result: ";
    std::cin >> in_text;

    std::cout << "to_upper_case: " << mystd::to_upper_case(in_text) << '\n';
    std::cout << "to_lower_case: " << mystd::to_lower_case(in_text) << '\n';
    std::cout << "string_length: " << mystd::string_length(in_text) << '\n';
    std::cout << std::boolalpha;
    std::cout << "eq1: " << mystd::string_equal(in_text, compare_text1) << '\n';
    std::cout << "eq2: " << mystd::string_equal(in_text, compare_text2) << '\n';

    return 0;
}
```
