#include <iostream>

float convertMillisecondsToSeconds(float);
float convertSecondsToMinutes(float);
float convertMinutesToHours(float);

float convertMillisecondsToMinutes(float);
float convertMillisecondsToHours(float);
float convertSecondsToHours(float);

int main()
{
    float InputMilliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> InputMilliseconds;

    float Seconds = convertMillisecondsToSeconds(InputMilliseconds);
    float Minutes = convertSecondsToMinutes(Seconds);
    float Hours = convertMinutesToHours(Minutes);

    float Minutes2 = convertMillisecondsToMinutes(InputMilliseconds);
    float Hours2 = convertMillisecondsToHours(InputMilliseconds);
    float Hours3 = convertSecondsToHours(Seconds);

    std::cout << "Seconds: " << Seconds << std::endl;
    std::cout << "Minutes: " << Minutes << std::endl;
    std::cout << "Hours: " << Hours << std::endl;

    std::cout << "Minutes2: " << Minutes2 << std::endl;
    std::cout << "Hours2: " << Hours2 << std::endl;
    std::cout << "Hours3: " << Hours3 << std::endl;

    return 0;
}

float convertMillisecondsToSeconds(float Millisconds)
{
    return Millisconds / 1000.0F;
}

float convertSecondsToMinutes(float Seconds)
{
    return Seconds / 60.0F;
}

float convertMinutesToHours(float Minutes)
{
    return Minutes / 60.0F;
}

float convertMillisecondsToMinutes(float Millisconds)
{
    float Seconds = convertMillisecondsToSeconds(Millisconds);
    float Minutes = convertSecondsToMinutes(Seconds);

    return Minutes;
}

float convertMillisecondsToHours(float Millisconds)
{
    float Seconds = convertMillisecondsToSeconds(Millisconds);
    float Minutes = convertSecondsToMinutes(Seconds);
    float Hours = convertMinutesToHours(Minutes);

    return Hours;
}


float convertSecondsToHours(float Seconds)
{
    float Minutes = convertSecondsToMinutes(Seconds);
    float Hours = convertMinutesToHours(Minutes);

    return Hours;
}
