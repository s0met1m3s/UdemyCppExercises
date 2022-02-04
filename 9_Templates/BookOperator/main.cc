#include <iostream>

#include "Book.hpp"

int main()
{
    Book b1("Harry Potter - Stein der Weisen", "J. K. Rowling", 1997);
    Book b2("Harry Potter - Die Kammer des Schreckens", "J. K. Rowling", 1998);

    std::cout << b1 << '\n';
    std::cout << b2 << '\n';

    std::cout << std::boolalpha;
    std::cout << (b1 == b2) << '\n';
    std::cout << (b1 == b1) << '\n';

    return 0;
}
