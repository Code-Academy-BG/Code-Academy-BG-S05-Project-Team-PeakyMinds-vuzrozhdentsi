#ifndef POINT_H
#define POINT_H

#include<string>

class Point
{
private:
    int x;
    int y;
public:
    // Point();
    Point(int xVal =0, int yVal =0);
    void set(int xVal, int yVal);
    std::string toString();
};
#endif