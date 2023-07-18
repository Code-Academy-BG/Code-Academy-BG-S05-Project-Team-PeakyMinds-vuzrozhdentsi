#ifndef PIN_H
#define PIN_H

#include <string>
#include <sstream>
#include "Point.hpp"
class Point;

class Pin
{
private:
  using idType = int;

  idType id;
  Point point;

public:
  Pin(idType id = 0, int x = 0, int y = 0);
  Pin(idType id, Point p);
  Pin(std::istream & stream);

  idType getId() const
  {
    return id;
  }
  Point getPoint() const
  {
    return point;
  }
  void setPosition(int x, int y)
  {
    point.set(x, y);
  }
  std::string toString();
  std::string toMachineLevelFormatString();
  // std::string serialize() const;
  // Pin deserialize(std::stringstream &strm);
  friend bool operator<(const Pin &p1, const Pin &p2);
  friend bool operator==(const Pin &p1, const Pin &p2);
  friend bool operator<=(const Pin &p1, const Pin &p2);
  friend bool operator!=(const Pin &p1, const Pin &p2);
  friend std::ostream &operator<<(std::ostream &stream, const Pin &p)
  {
    stream << p.getId() << ' ' << p.getPoint();
    return stream;
  }
  friend std::istream &operator>>(std::istream &stream, Pin &p)
  {
    stream >> p.id >> p.point;
    return stream;
  }
};

#endif
