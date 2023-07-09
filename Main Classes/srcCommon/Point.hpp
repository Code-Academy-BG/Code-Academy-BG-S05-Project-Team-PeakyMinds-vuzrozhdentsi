#ifndef POINT_H
#define POINT_H

#include <string>
#include<sstream>

class Point
{
public:
    static const unsigned int BIT8 = 8;

private:
    int x;
    int y;

public:
    Point(): x{0},y{0}{};
    Point(int xVal, int yVal) : x(xVal), y(yVal)
    {
    }
    Point(std::istream & stream) { stream >> *this;}
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
    // std::string serialize() const
    // {
    //     std::string result{""};
    //     result.append(std::to_string(getX())).append(" ").append(std::to_string(getY()));
    //     return result;
    // }
    // Point deserialize(std::stringstream & strm)
    // {
        
    //     std::string lineX{0}, lineY{0};
    //     Point p;
    //     strm>>lineX >> lineY;
    //     p.set(std::stoi(lineX), std::stoi(lineY));
    //     return p;
    // }
    friend bool operator<(const Point & p1, const Point & p2)
    {
        return (p1.x < p2.x && p1.y <= p2.y)
            || (p1.x <= p2.x && p1.y < p2.y);
    }
    friend bool operator==(const Point & p1, const Point & p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    friend bool operator!=(const Point & p1, const Point & p2)
    {
        return !(p1==p2);
    }
    friend std::ostream& operator<<(std::ostream & stream, const Point& p)
    {
            stream<<p.x<<' '<<p.y<<' ';
            return stream;
    }
    friend std::istream& operator>>(std::istream & stream, Point& p)
    {
        stream >> p.x>>p.y;
        return stream;
    }
};
#endif