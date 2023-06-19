#include "Pin.hpp"

Pin::Pin(int id, int x, int y) : id{id}, point{x,y}
{
}

std::string Pin::toString()
{
    return this->point.toString();
}

std::string Pin::toMachineLevelFormatString()
{
    return this->point.toMachineLevelFormatString();
}

bool operator<(const Pin & p1, const Pin & p2)
{
    return p1.getPoint() < p2.getPoint();
}
bool operator==(const Pin & p1, const Pin & p2)
{
    return p1.getPoint() == p2.getPoint();
}
bool operator!=(const Pin & p1, const Pin & p2)
{
    return !(p1.getPoint() == p2.getPoint());
}