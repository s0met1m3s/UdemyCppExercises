#pragma once

#include <cstdint>
#include <vector>

struct ScrollingBuffer
{
    size_t MaxSize;
    size_t Offset;
    std::vector<float> Data_x;
    std::vector<float> Data_y;

    ScrollingBuffer(const size_t max_size)
    {
        MaxSize = max_size;
        Offset = 0;
    }

    void AddPoint(const float x, const float y)
    {
        if (Data_x.size() < MaxSize)
        {
            Data_x.push_back(x);
            Data_y.push_back(y);
        }
        else
        {
            Data_x[Offset] = x;
            Data_y[Offset] = y;
            Offset = (Offset + 1) % MaxSize;
        }
    }

    void Erase()
    {
        if (Data_x.size() > 0)
        {
            Data_x.clear();
            Data_y.clear();
            Offset = 0;
        }
    }
};
