#pragma once

#include <cstdint>
#include <vector>

struct ScrollingBuffer
{
    size_t max_size;
    size_t offset;
    size_t last_offset;

    std::vector<float> data_x;
    std::vector<float> data_y;

    ScrollingBuffer(const size_t size)
    {
        max_size = size;
        offset = 0;
        last_offset = 0;
    }

    void AddPoint(const float x, const float y)
    {
        if (data_x.size() < max_size)
        {
            data_x.push_back(x);
            data_y.push_back(y);
        }
        else
        {
            data_x[offset] = x;
            data_y[offset] = y;
            last_offset = offset;
            offset = (offset + 1) % max_size;
        }
    }

    void Erase()
    {
        if (data_x.size() > 0)
        {
            data_x.clear();
            data_y.clear();
            offset = 0;
            last_offset = 0;
        }
    }
};
