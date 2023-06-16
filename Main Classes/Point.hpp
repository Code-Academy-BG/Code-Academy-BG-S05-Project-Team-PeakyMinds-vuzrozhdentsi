#ifndef POINT_H
#define POINT_H

#include<string>

class Point
{
<<<<<<< Updated upstream
public:
    static const unsigned int BIT8 = 8; 
private:
=======
    private:
>>>>>>> Stashed changes
    int x;
    int y;
public:
    // Point();
<<<<<<< Updated upstream
    Point(int xVal =0, int yVal =0);
    void set(int xVal, int yVal);
    std::string toString();
    std::string toMachineLevelFormatString(unsigned int bits = BIT8);
=======
>>>>>>> Stashed changes
};
#endif