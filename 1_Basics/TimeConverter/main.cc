#include <iostream>

float convertMillisecondsToSeconds(float);
float convertSecondsToMinutes(float);
float convertMinutesToHours(float);

int main()
{
    float InputMilliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> InputMilliseconds;

    float Seconds = convertMillisecondsToSeconds(InputMilliseconds);
    float Minutes = convertSecondsToMinutes(Seconds);
    float Hours = convertMinutesToHours(Minutes);

    std::cout << Seconds << std::endl;
    std::cout << Minutes << std::endl;
    std::cout << Hours << std::endl;

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
