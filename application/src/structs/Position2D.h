#pragma once
#include <assert.h>
struct Position2D
{
    float x;
    float y;
    Position2D operator +=(Position2D other)
    {
        return Position2D{ this->x + other.x,this->y + other.y };
    }
    Position2D operator -=(Position2D other)
    {
        return Position2D{ this->x - other.x,this->y - other.y };
    }
    float* operator [](int index)
    {
        assert(!(index > 2 || index < 0), "Indexing out of bounds");
        return index == 0 ? &x : &y;
    }
};