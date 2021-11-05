#pragma once

#include <iostream>
#include <string>

class Book
{
    friend std::istream &operator>>(std::istream &, Book &);
    friend std::ostream &operator<<(std::ostream &, const Book &);
    friend bool operator==(const Book &, const Book &);
    friend bool operator!=(const Book &, const Book &);

public:
    Book() = delete;
    Book(std::string name_, std::string author_, std::uint32_t pubyear_);
    Book(std::istream &in);
    ~Book() = default;

private:
    std::string name;
    std::string author;
    std::uint32_t pubyear;
};

std::istream &operator>>(std::istream &, Book &);
std::ostream &operator<<(std::ostream &, const Book &);
bool operator==(const Book &, const Book &);
bool operator!=(const Book &, const Book &);
