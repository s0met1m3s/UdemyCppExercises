#include <algorithm>

#include "lib.h"

// RE-USE THESE FUNCTIONS FOR THE STRINGS
namespace
{
static bool is_upper_case_(const char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return true;
    }

    return false;
}

static bool is_lower_case_(const char character)
{
    if ((character >= 'a') && (character <= 'z'))
    {
        return true;
    }

    return false;
}

static char to_upper_case_(const char character)
{
    if (is_lower_case_(character))
    {
        return character + 32;
    }

    return character;
}

static char to_lower_case_(const char character)
{
    if (is_upper_case_(character))
    {
        return character + 32;
    }

    return character;
}
} // namespace

namespace mystd
{

std::string to_upper_case(std::string_view text)
{

}

std::string to_lower_case(std::string_view text)
{

}

std::size_t string_length(std::string_view text)
{
}

bool string_equal(std::string_view string1, std::string_view string2)
{
}

} // namespace mystd
