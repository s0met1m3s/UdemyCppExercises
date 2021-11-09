#include <iostream>
#include <list>

#include "IteratorLib.hpp"

int main()
{
    std::list<int> list{1, 2, 3};
    auto list_it = list.begin();

    auto next_it = mystd::next(list_it);
    std::cout << "*next_it: " << *next_it << std::endl;

    auto prev_it = mystd::prev(list_it);
    std::cout << "*prev_it: " << *prev_it << std::endl;

    mystd::advance(list_it, 2);
    std::cout << "*list_it: " << *list_it << std::endl;

    auto dist = mystd::distance(list_it, list.begin());
    std::cout << "dist: " << dist << std::endl;

    return 0;
}
