#include "Pin.hpp"

// Pin::Pin() : id {0}, point() {}

Pin::Pin(int id, int x, int y) : id{id}, point(x,y)
{
}

const int Pin::getId() const
{
        return this->id;
}

void Pin::setPosition(int x, int y)
{
    this->point.set(x,y);
}

std::string Pin::toString()
{
    return this->point.toString();
}

std::string Pin::toMachineLevelFormatString()
{
    return this->point.toMachineLevelFormatString();
}