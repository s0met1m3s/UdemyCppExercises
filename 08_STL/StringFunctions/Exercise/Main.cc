#include <iostream>
#include <string>

#include "StringFunctions.hpp"

int main()
{
    std::string str1 = "anna";
    std::cout << std::boolalpha << str1
              << " is_palindrom: " << mystd::is_palindrom(str1) << '\n';

    std::string str2 = "JanIstHier";
    std::cout << std::boolalpha << str2
              << " starts_with: Jan = " << mystd::starts_with(str2, "Jan")
              << '\n';
    std::cout << std::boolalpha << str2
              << " starts_with: Ja = " << mystd::starts_with(str2, "Ja")
              << '\n';
    std::cout << std::boolalpha << str2
              << " starts_with: ja = " << mystd::starts_with(str2, "ja")
              << '\n';

    std::string str3 = "JanWarHier";
    std::cout << std::boolalpha << str3
              << " ends_with: Hier = " << mystd::ends_with(str3, "Hier")
              << '\n';
    std::cout << std::boolalpha << str3
              << " ends_with: Hie = " << mystd::ends_with(str3, "Hie") << '\n';
    std::cout << std::boolalpha << str3
              << " ends_with: Hir = " << mystd::ends_with(str3, "Hir") << '\n';

    std::string str4 = "JanWarHier";
    std::cout << std::boolalpha << str4
              << " contains: Hier = " << mystd::contains(str4, "Hier") << '\n';
    std::cout << std::boolalpha << str4
              << " contains: War = " << mystd::contains(str4, "War") << '\n';
    std::cout << std::boolalpha << str4
              << " contains: jan = " << mystd::contains(str4, "jan") << '\n';

    std::string str5 = "HalloHallohaHallo";
    std::cout << "num_occurences: " << mystd::num_occurences(str5, "Hallo")
              << '\n';

    return 0;
}
