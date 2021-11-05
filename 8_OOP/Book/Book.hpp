#pragma once

#include <iostream>
#include <string>

class Book
{
    friend std::istream &operator>>(std::istream &, Book &);
    friend std::ostream &operator<<(std::ostream &, const Book &);

public:
    Book() = default;
    Book(std::string name_, std::string author_, std::uint32_t pubyear_);
    ~Book() = default;

    bool operator==(const Book &other) const;
    bool operator!=(const Book &other) const;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};

std::istream &operator>>(std::istream &, Book &);
std::ostream &operator<<(std::ostream &, const Book &);
