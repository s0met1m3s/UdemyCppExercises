#include <cstdint>

#include "lib.h"

float convert_milliseconds_to_seconds(float millisconds)
{
    return millisconds / 1000.0F;
}

float convert_seconds_to_minutes(float seconds)
{
    return seconds / 60.0F;
}

float convert_minutes_to_hours(float minutes)
{
    return minutes / 60.0F;
}

float convert_milliseconds_to_minutes(float millisconds)
{
    float seconds = convert_milliseconds_to_seconds(millisconds);
    float minutes = convert_seconds_to_minutes(seconds);

    return minutes;
}

float convert_milliseconds_to_hours(float millisconds)
{
    float seconds = convert_milliseconds_to_seconds(millisconds);
    float minutes = convert_seconds_to_minutes(seconds);
    float hours = convert_minutes_to_hours(minutes);

    return hours;
}

float convert_seconds_to_hours(float seconds)
{
    float minutes = convert_seconds_to_minutes(seconds);
    float hours = convert_minutes_to_hours(minutes);

    return hours;
}
