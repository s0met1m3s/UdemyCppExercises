# Exercise

Implement the following functions:

```cpp
template <typename StringType, typename ViewType>
StringType to_upper_case(ViewType text);

template <typename StringType, typename ViewType>
StringType to_lower_case(ViewType text);
```

## Main Function

```cpp
int main()
{
    auto input_text = std::string{};
    std::cout << "Please enter any text: ";
    std::cin >> input_text;

    std::cout << "to_upper_case: " << to_upper_case<std::string, std::string_view>(input_text)
              << std::endl;
    std::cout << "to_lower_case: " << to_lower_case<std::string, std::string_view>(input_text)
              << std::endl;

    auto input_text_w = std::wstring(input_text.begin(), input_text.end());
    to_upper_case<std::wstring, std::wstring_view>(input_text_w);
    to_lower_case<std::wstring, std::wstring_view>(input_text_w);

    // auto input_text_c = input_text.c_str();
    // to_upper_case(input_text_c);
    // to_lower_case(input_text_c);

    return 0;
}
```
