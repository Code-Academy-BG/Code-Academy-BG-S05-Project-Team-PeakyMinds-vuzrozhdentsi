#ifndef POINT_H
#define POINT_H

#include<string>

class Point
{
public:
    static const unsigned int BIT8 = 8; 
private:
    int x;
    int y;
public:
    // Point();
    Point(int xVal =0, int yVal =0);
    void set(int xVal, int yVal);
    std::string toString();
    std::string toMachineLevelFormatString(unsigned int bits = BIT8);
};
#endif