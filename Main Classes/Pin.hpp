#ifndef PIN_H
#define PIN_H

#include<string>
#include<sstream>
#include"Point.hpp"
#include"PointFactory.hpp"
 class Point;

 class Pin
 {
  public:
    static PointFactory factory;
 private:  

  using idType = int;
  using RawMaterial = PointFactory::FactoryRawMaterial;
  using FactoryTypePtr = PointFactory::FactoryType;

    idType id;
    FactoryTypePtr point;
 public:
    Pin(idType id=0, int x=0, int y=0);
    Pin(idType id, Point p);
    
    idType getId() const
    {
      return this->id;
    }
    RawMaterial getPoint() const
    {
      return *this->point;
    }
    FactoryTypePtr getPointPtr() const
    {
      return this->point;
    }
    void setPosition(int x, int y)
    {
      point = factory.getInstancePointer(Point(x,y));
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

