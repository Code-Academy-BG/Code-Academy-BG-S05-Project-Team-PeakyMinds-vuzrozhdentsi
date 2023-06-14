#include "Point.hpp"

// Point::Point(): x{0},y{0} {};

Point::Point(int xVal, int yVal): x{xVal}, y{yVal} {};

void Point::set(int xVal, int yVal){
    this->x = xVal;
    this->y = yVal;
}

std::string Point::toString(){
    std::string s{""};
    s = '(' + this->x + ',' + this->y + ')';
    return s;
}