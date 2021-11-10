#include <string_view>

#include "Book.hpp"

Book::Book(std::string_view name_, std::string_view author_, std::uint32_t pubyear_)
    : name(name_), author(author_), pubyear(pubyear_)
{
}

bool Book::operator==(const Book &other) const
{
    return ((this->name == other.name) && (this->author == other.author) && (this->pubyear == other.pubyear));
}

bool Book::operator!=(const Book &other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const Book &book)
{
    out << book.name << " " << book.author << " " << book.pubyear << std::endl;
    return out;
}
