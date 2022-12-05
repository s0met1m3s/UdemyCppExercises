#include <iostream>
#include <vector>

#include "Lib.h"

int main()
{
    std::vector<int> vec{1, 2, 3};
    auto vec_it = vec.begin();

    auto next_it = mystd::next(vec_it);
    std::cout << "*next_it: " << *next_it << '\n';

    auto prev_it = mystd::prev(next_it);
    std::cout << "*prev_it: " << *prev_it << '\n';

    mystd::advance(vec_it, 2);
    std::cout << "advance: " << *vec_it << '\n';

    auto dist = mystd::distance(vec_it, vec.end());
    std::cout << "distance: " << dist << '\n';

    return 0;
}
