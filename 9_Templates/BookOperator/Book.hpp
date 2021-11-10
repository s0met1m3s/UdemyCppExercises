#pragma once

#include <iostream>
#include <string>

class Book
{
    friend std::ostream &operator<<(std::ostream &, const Book &);

public:
    Book() = default;
    Book(std::string_view name_, std::string_view author_, std::uint32_t pubyear_);
    ~Book() noexcept = default;

    bool operator==(const Book &other) const;
    bool operator!=(const Book &other) const;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};

std::ostream &operator<<(std::ostream &, const Book &);
