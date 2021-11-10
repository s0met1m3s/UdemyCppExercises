#pragma once

#include <iostream>
#include <string>

class Book
{
public:
    Book() = default;
    Book(std::string name_, std::string author_, std::uint32_t pubyear_);
    ~Book() noexcept = default;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};
