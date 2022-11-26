#pragma once

#include <cstdint>
#include <iostream>
#include <string_view>

class Book
{
public:
    Book() = default;
    Book(std::string_view name_,
         std::string_view author_,
         std::uint32_t pubyear_);
    ~Book() noexcept = default;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};
