#include <iostream>

/* CHARS */

bool isNumeric(char Character);
bool isAlpha(char Character);
bool isAlphaNumeric(char Character);
bool isUpperCase(char Character);
bool isLowerCase(char Character);

char toUpperCase(char Character);
char toLowerCase(char Character);

/* CHAR ARRAYS */

char *toUpperCase(char *Text);
char *toLowerCase(char *Text);

std::size_t stringLength(char *Text);
char *charSearch(char *Text, char Character);

int main()
{
    char InputText[50] = {};

    std::cout << "Please enter any Text: ";
    std::cin >> InputText;

    std::cout << "toUpperCase: " << toUpperCase(InputText) << std::endl;
    std::cout << "toLowerCase: " << toLowerCase(InputText) << std::endl;
    std::cout << "stringLength: " << stringLength(InputText) << std::endl;
    std::cout << "charSearch: " << charSearch(InputText, 'a') << std::endl;

    return 0;
}

/* CHARS */

bool isNumeric(char Character)
{
    if ((Character >= '0') && (Character <= '9'))
    {
        return true;
    }

    return false;
}

bool isAlpha(char Character)
{
    if (isUpperCase(Character) || isLowerCase(Character))
    {
        return true;
    }

    return false;
}

bool isAlphaNumeric(char Character)
{
    return isNumeric(Character) || isAlpha(Character);
}

bool isUpperCase(char Character)
{
    if ((Character >= 'A') && (Character <= 'Z'))
    {
        return true;
    }

    return false;
}

bool isLowerCase(char Character)
{
    if ((Character >= 'a') && (Character <= 'z'))
    {
        return true;
    }

    return false;
}

char toUpperCase(char Character)
{
    if (isLowerCase(Character))
    {
        return Character - 32;
    }

    return Character;
}

char toLowerCase(char Character)
{
    if (isUpperCase(Character))
    {
        return Character + 32;
    }

    return Character;
}

/* CHAR ARRAYS */

char *toUpperCase(char *Text)
{
    char *CurrentCharacter = Text;

    while (*CurrentCharacter != '\0')
    {
        if (isLowerCase(*CurrentCharacter))
        {
            *CurrentCharacter = *CurrentCharacter - 32;
        }

        CurrentCharacter++;
    }

    return Text;
}

char *toLowerCase(char *Text)
{
    char *CurrentCharacter = Text;

    while (*CurrentCharacter != '\0')
    {
        if (isUpperCase(*CurrentCharacter))
        {
            *CurrentCharacter = *CurrentCharacter + 32;
        }

        CurrentCharacter++;
    }

    return Text;
}

std::size_t stringLength(char *Text)
{
    std::size_t Length = 0;

    while (*Text != '\0')
    {
        Length++;
        Text++;
    }

    return Length;
}

char *charSearch(char *Text, char Character)
{
    while ((*Text != Character) && (*Text != '\0'))
    {
        Text++;
    }

    return Text;
}
