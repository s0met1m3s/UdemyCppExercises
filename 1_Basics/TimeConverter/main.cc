#include <iostream>

float convert_milliseconds_to_seconds(float Millisconds);

float convert_seconds_to_minutes(float seconds);

float convert_minutes_to_hours(float Minutes);

float convert_milliseconds_to_minutes(float Millisconds);

float convert_milliseconds_to_hours(float Millisconds);

float convert_seconds_to_hours(float seconds);

int main()
{
    float Input_milliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> Input_milliseconds;

    float seconds = convert_milliseconds_to_seconds(Input_milliseconds);
    float Minutes = convert_seconds_to_minutes(seconds);
    float Hours = convert_minutes_to_hours(Minutes);

    float Minutes2 = convert_milliseconds_to_minutes(Input_milliseconds);
    float Hours2 = convert_milliseconds_to_hours(Input_milliseconds);
    float Hours3 = convert_seconds_to_hours(seconds);

    std::cout << "seconds: " << seconds << std::endl;
    std::cout << "Minutes: " << Minutes << std::endl;
    std::cout << "Hours: " << Hours << std::endl;

    std::cout << "Minutes2: " << Minutes2 << std::endl;
    std::cout << "Hours2: " << Hours2 << std::endl;
    std::cout << "Hours3: " << Hours3 << std::endl;

    return 0;
}

float convert_milliseconds_to_seconds(float Millisconds)
{
    return Millisconds / 1000.0F;
}

float convert_seconds_to_minutes(float seconds)
{
    return seconds / 60.0F;
}

float convert_minutes_to_hours(float Minutes)
{
    return Minutes / 60.0F;
}

float convert_milliseconds_to_minutes(float Millisconds)
{
    float seconds = convert_milliseconds_to_seconds(Millisconds);
    float Minutes = convert_seconds_to_minutes(seconds);

    return Minutes;
}

float convert_milliseconds_to_hours(float Millisconds)
{
    float seconds = convert_milliseconds_to_seconds(Millisconds);
    float Minutes = convert_seconds_to_minutes(seconds);
    float Hours = convert_minutes_to_hours(Minutes);

    return Hours;
}


float convert_seconds_to_hours(float seconds)
{
    float Minutes = convert_seconds_to_minutes(seconds);
    float Hours = convert_minutes_to_hours(Minutes);

    return Hours;
}
