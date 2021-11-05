#include "Book.hpp"

Book::Book(std::string name_, std::string author_, std::uint32_t pubyear_)
    : name(name_), author(author_), pubyear(pubyear_)
{
}

bool Book::operator==(const Book &other) const
{
    return ((this->name == other.name) && (this->author == other.author) &&
            (this->pubyear == other.pubyear));
}

bool Book::operator!=(const Book &other) const
{
    return !(*this == other);
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
