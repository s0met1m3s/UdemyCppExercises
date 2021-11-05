#include "Book.hpp"

Book::Book(std::string name_, std::string author_, std::uint32_t pubyear_)
    : name(name_), author(author_), pubyear(pubyear_)
{
}

Book::Book(std::istream &in)
{
    in >> *this;
}

std::istream &operator>>(std::istream &in, Book &book)
{
    in >> book.name >> book.author >> book.pubyear;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Book &book)
{
    out << book.name << " " << book.author << " " << book.pubyear << std::endl;
    return out;
}

bool operator==(const Book &lhs, const Book &rhs)
{
    return ((lhs.name == rhs.name) && (lhs.author == rhs.author) && (lhs.pubyear == rhs.pubyear));
}

bool operator!=(const Book &lhs, const Book &rhs)
{
    return !((lhs.name == rhs.name) && (lhs.author == rhs.author) && (lhs.pubyear == rhs.pubyear));
}
