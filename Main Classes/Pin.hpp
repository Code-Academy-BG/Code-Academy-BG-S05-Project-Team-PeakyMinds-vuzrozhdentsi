#ifndef PIN_H
#define PIN_H

#include<string>
#include<sstream>
#include"Point.hpp"
 class Point;

 class Pin
 {
 private:    
    int id;
    Point point;
 public:
    Pin(int id=0, int x=0, int y=0);
    Pin(int id, Point p);
    
    int getId() const
    {
      return this->id;
    }
    Point getPoint() const
    {
      return this->point;
    }
    void setPosition(int x, int y)
    {
      this->point.set(x,y);
    }
    std::string toString();
    std::string toMachineLevelFormatString();
    std::string serialize() const;
    Pin deserialize(std::stringstream & strm);
    friend bool operator<(const Pin & p1, const Pin & p2);
    friend bool operator==(const Pin & p1, const Pin & p2);
    friend bool operator!=(const Pin & p1, const Pin & p2);
    
 };

#endif

