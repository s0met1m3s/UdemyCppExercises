#include <string_view>

#include "Book.hpp"

Book::Book(std::string_view name_, std::string_view author_, std::uint32_t pubyear_)
    : name(name_), author(author_), pubyear(pubyear_)
{
}

bool Book::operator==(const Book &other) const
{
    const auto same_name = (name == other.name);
    const auto same_author = (author == other.author);
    const auto same_pubyear = (pubyear == other.pubyear);
    return (same_name && same_author && same_pubyear);
}

bool Book::operator!=(const Book &other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const Book &book)
{
    out << book.name << " " << book.author << " " << book.pubyear << "\n";
    return out;
}
