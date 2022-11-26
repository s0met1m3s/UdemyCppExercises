#include <string_view>

#include "Book.hpp"

Book::Book(std::string_view name_,
           std::string_view author_,
           std::uint32_t pubyear_)
    : name(name_), author(author_), pubyear(pubyear_)
{
}
