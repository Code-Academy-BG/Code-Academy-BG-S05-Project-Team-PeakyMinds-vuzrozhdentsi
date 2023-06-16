#ifndef PIN_H
#define PIN_H

#include<string>
#include"Point.hpp"
 class Point;

 class Pin
 {
 private:    
    int id;
    Point point;
 public:
    // Pin();
    Pin(int id, int x=0, int y=0) : id(id)
    {}
    const int getId() const
    {
      return this->id;
    }
    void setPosition(int x, int y)
    {
      point.x
    }
    std::string toString();
    std::string toMachineLevelFormatString();
 };

#endif

