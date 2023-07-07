#include "Pin.hpp"

Pin::Pin(int id, int x, int y) : id{id}, point{x,y}
{
}
Pin::Pin(int id, Point pnt): id{id}, point{pnt}
{
}
Pin::Pin(std::istream & stream)
{
    stream >> *this;
}

std::string Pin::toString()
{
    return getPoint().toString();
}

std::string Pin::toMachineLevelFormatString()
{
    return getPoint().toMachineLevelFormatString();
}
// std::string Pin::serialize() const
// {
//     std::string result{""};
//     result.append(std::to_string( getId())).append(" ").append(getPoint().serialize());
//     return result;
// }
// Pin Pin::deserialize(std::stringstream & strm)
// {
//     Point point;
//     std::string id;
//     strm >> id;
//     point = point.deserialize(strm);
//     Pin pin(std::stoi(id),point);
//     return pin;   
// }
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