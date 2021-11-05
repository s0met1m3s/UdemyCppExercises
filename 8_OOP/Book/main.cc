#include <iostream>

#include "Book.hpp"

int main()
{
    Book b1("Harry Potter - Stein der Weisen", "J. K. Rowling", 1996);
    Book b2("Harry Potter - Die Kammer des Schreckens", "J. K. Rowling", 1998);

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;

    std::cout << std::boolalpha;
    std::cout << (b1 == b2) << std::endl;
    std::cout << (b1 == b1) << std::endl;

    return 0;
}
