#ifndef POINT_H
#define POINT_H

#include <string>

class Point
{
public:
    static const unsigned int BIT8 = 8;

private:
private:
    int x;
    int y;

public:
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal)
    {
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
    std::string Point::toMachineLevelFormatString(unsigned int bits = BIT8)
    {
        unsigned long res{0};
        res |= this->x;
        res <<= bits;
        res |= this->y;
        return std::to_string(res);
    }
};
#endif