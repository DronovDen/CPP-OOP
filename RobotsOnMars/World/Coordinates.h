#pragma once

class Coordinates
{
public:
    size_t x;
    size_t y;

    Coordinates(size_t new_x, size_t new_y) : x{new_x}, y{new_y} {};
    Coordinates() : x{ 0 }, y{ 0 }{};
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
    /*bool operator==(const Coordinates &point) const
    {
        return (point.x == x && point.x == y);
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