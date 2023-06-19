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
    Pin(int id=0, int x=0, int y=0);
    
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
      point.set(x,y);
      this->point.set(x,y);
    }
    std::string toString();
    std::string toMachineLevelFormatString();
    friend bool operator<(const Pin & p1, const Pin & p2);
    friend bool operator==(const Pin & p1, const Pin & p2);
    friend bool operator!=(const Pin & p1, const Pin & p2);
    
 };

#endif

