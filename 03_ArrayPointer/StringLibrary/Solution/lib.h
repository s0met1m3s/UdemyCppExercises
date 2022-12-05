#pragma once

#include <cstdlib>

/** START PREV FUNCS **/

bool is_numeric(char character);

bool is_alpha(char character);

bool is_alpha_numeric(char character);

bool is_upper_case(char character);

bool is_lower_case(char character);

char to_upper_case(char character);

char to_lower_case(char character);

/** END PREV FUNCS **/

char *to_upper_case(char *text);

char *to_lower_case(char *text);

std::size_t string_length(const char *text);

char *char_search(char *text, char character);

bool string_equal(const char *string1, const char *string2);
