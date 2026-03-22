#pragma once
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
};