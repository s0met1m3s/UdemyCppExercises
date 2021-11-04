#include <iostream>

float convert_millisecondsTo_seconds(float Millisconds);
float convert_secondsTo_minutes(float Seconds);
float convert_minutesTo_hours(float Minutes);

float convert_millisecondsTo_minutes(float Millisconds);
float convert_millisecondsTo_hours(float Millisconds);
float convert_secondsTo_hours(float Seconds);

int main()
{
    float Input_milliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> Input_milliseconds;

    float Seconds = convert_millisecondsTo_seconds(Input_milliseconds);
    float Minutes = convert_secondsTo_minutes(Seconds);
    float Hours = convert_minutesTo_hours(Minutes);

    float Minutes2 = convert_millisecondsTo_minutes(Input_milliseconds);
    float Hours2 = convert_millisecondsTo_hours(Input_milliseconds);
    float Hours3 = convert_secondsTo_hours(Seconds);

    std::cout << "Seconds: " << Seconds << std::endl;
    std::cout << "Minutes: " << Minutes << std::endl;
    std::cout << "Hours: " << Hours << std::endl;

    std::cout << "Minutes2: " << Minutes2 << std::endl;
    std::cout << "Hours2: " << Hours2 << std::endl;
    std::cout << "Hours3: " << Hours3 << std::endl;

    return 0;
}

float convert_millisecondsTo_seconds(float Millisconds)
{
    return Millisconds / 1000.0F;
}

float convert_secondsTo_minutes(float Seconds)
{
    return Seconds / 60.0F;
}

float convert_minutesTo_hours(float Minutes)
{
    return Minutes / 60.0F;
}

float convert_millisecondsTo_minutes(float Millisconds)
{
    float Seconds = convert_millisecondsTo_seconds(Millisconds);
    float Minutes = convert_secondsTo_minutes(Seconds);

    return Minutes;
}

float convert_millisecondsTo_hours(float Millisconds)
{
    float Seconds = convert_millisecondsTo_seconds(Millisconds);
    float Minutes = convert_secondsTo_minutes(Seconds);
    float Hours = convert_minutesTo_hours(Minutes);

    return Hours;
}


float convert_secondsTo_hours(float Seconds)
{
    float Minutes = convert_secondsTo_minutes(Seconds);
    float Hours = convert_minutesTo_hours(Minutes);

    return Hours;
}
