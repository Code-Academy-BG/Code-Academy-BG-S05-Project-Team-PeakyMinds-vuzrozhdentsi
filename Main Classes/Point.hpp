#ifndef POINT_H
#define POINT_H

#include <string>

class Point
{
public:
    static const unsigned int BIT8 = 8;

private:
    int x;
    int y;

public:
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal)
    {
    }
    int getX() const
    {
        return this->x;
    }
    int getY() const
    {
        return this->y;
    }
    void set(int xVal, int yVal)
    {
        this->x = xVal;
        this->y = yVal;
    }
    std::string toString()
    {
        return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }
    std::string toString() const
    {
        return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }
    std::string toMachineLevelFormatString(unsigned int bits = BIT8)
    {
        unsigned long res{0};
        res |= this->x;
        res <<= bits;
        res |= this->y;
        return std::to_string(res);
    }
    std::string toMachineLevelFormatString(unsigned int bits = BIT8) const
    {
        unsigned long res{0};
        res |= this->x;
        res <<= bits;
        res |= this->y;
        return std::to_string(res);
    }
    friend bool operator<(const Point & p1, const Point & p2)
    {
        return (p1.x < p2.x && p1.y < p2.y)
            || (p1.x < p2.x && p1.y == p2.y)
            || (p1.x == p2.x && p1.y < p2.y);
    }
    friend bool operator==(const Point & p1, const Point & p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    friend bool operator!=(const Point & p1, const Point & p2)
    {
        return !(p1==p2);
    }
};
#endif