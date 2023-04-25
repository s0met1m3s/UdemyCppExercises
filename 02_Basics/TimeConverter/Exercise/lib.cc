#include <cstdint>

#include "lib.h"

float convert_milliseconds_to_seconds(const float milliseconds)
{
   float milli_to_Sec = milliseconds / 1000;

   return milli_to_Sec;

}

float convert_seconds_to_minutes(const float seconds)
{
    float Sec_to_Min = seconds / 60;

    return Sec_to_Min;
}

float convert_minutes_to_hours(const float minutes)
{
   float min_to_hours =  minutes / 60;

   return min_to_hours;
}

float convert_milliseconds_to_minutes(const float milliseconds)
{
   float milli_to_min =  milliseconds / 1000 / 60;

   return milli_to_min;
}

float convert_milliseconds_to_hours(const float milliseconds)
{
    float milli_to_hours = milliseconds / 1000 / 60 / 60;

    return milli_to_hours;
}

float convert_seconds_to_hours(const float seconds)
{
    float sec_to_hours = seconds / 60 / 60;

    return sec_to_hours;
}
