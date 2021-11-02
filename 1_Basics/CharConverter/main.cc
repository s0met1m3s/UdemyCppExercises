#include <iostream>

bool isNumeric(char Character);
bool isAlpha(char Character);
bool isAlphaNumeric(char Character);
bool isUpperCase(char Character);
bool isLowerCase(char Character);

char toUpperCase(char Character);
char toLowerCase(char Character);

int main()
{
    char InputCharacter;

    std::cout << "Please enter any ASCII character: ";
    std::cin >> InputCharacter;

    std::cout << std::boolalpha;
    std::cout << "isNumeric: " << isNumeric(InputCharacter) << std::endl;
    std::cout << "isAlpha: " << isAlpha(InputCharacter) << std::endl;
    std::cout << "isAlphaNumeric: " << isAlphaNumeric(InputCharacter) << std::endl;
    std::cout << "isUpperCase: " << isUpperCase(InputCharacter) << std::endl;
    std::cout << "isLowerCase: " << isLowerCase(InputCharacter) << std::endl;
    std::cout << std::dec;
    std::cout << "toUpperCase: " << toUpperCase(InputCharacter) << std::endl;
    std::cout << "toLowerCase: " << toLowerCase(InputCharacter) << std::endl;

    return 0;
}

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
