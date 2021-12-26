#pragma once

class Coordinates
{
public:
    size_t x;
    size_t y;

    Coordinates(size_t x, size_t y) : x{x}, y{y} {};
    Coordinates() = default;
    void setXY(size_t x, size_t y)
    {
        x = x;
        y = y;
    }
    const Coordinates *previous{nullptr};

    Coordinates operator-(const Coordinates &r)
    {
        Coordinates temp;
        temp.x = this->x - r.x;
        temp.y = this->y - r.y;
        return temp;
    }
    /*bool operator==(const Coordinates &posize_t) const
    {
        return (posize_t.x == x && posize_t.x == y);
    }*/
    friend bool operator==(const Coordinates &r, const Coordinates &l)
    {
        return ((r.x == l.x) && (r.y == l.y));
    }
    friend bool operator!=(const Coordinates &r, const Coordinates &l)
    {
        return !(r == l);
    }
    friend bool operator<(const Coordinates &r, const Coordinates &l)
    {
        return ((r.x < l.x) && (r.y < l.y));
    }
};