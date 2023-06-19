#ifndef ELECTRONIC_COMPONENT_H
#define ELECTRONIC_COMPONENT_H

#include <string>
#include <vector>
#include <algorithm>
#include "Pin.hpp"
#include "Point.hpp"

class ElectronicComponent
{

    enum class Rotation
    {
        Zero = 0,
        StraightAngle = 90,
        UTurn = 180,
        ThreeQuarters = 270
    };

private:
    std::string id;
    int height;
    int width;
    int boardOrderNumber;
    Rotation rotation;
    Point startingPosition;
    std::vector<Pin> pins;

private:
    static const unsigned int BIT8 = 8;
    std::string widthAndHeightToMachineLevelFormat(int bits = BIT8);

public:
    ElectronicComponent(std::string id = "", int height = 0, int width = 0, int boardOrderNumber = 0,
                        Point startingPosition = Point(0, 0), Rotation rotation = Rotation::Zero)
        : id{id}, height{height}, width{width}, boardOrderNumber{boardOrderNumber},
          startingPosition{startingPosition}, rotation{rotation}
    {
    }
    std::string getId() const
    {
        return this->id;
    }
    int getHeight() const
    {
        return this->height;
    }
    int getWidth() const
    {
        return this->width;
    }
    const Point &getStartingPosition() const
    {
        return this->startingPosition;
    }
    int getRotation() const;
    int getBoardOrderNumber() const
    {
        return this->boardOrderNumber;
    }
    std::vector<Pin> getPins() const
    {
       return this->pins;
    }
    void setStartingPosition(Point point);
    void setHeight(int h)
    {
        this->height = h;
    }
    void setWidth(int w)
    {
        this->width = w;
    }
    void setRotation(int quadrantNumber);
    void setBoardOrderNumber(int number)
    {
        this->boardOrderNumber = number;
    }

    void addPin(int x, int y) // this is the moment to Pin p.setid = vector index
    {
        Pin p(getPins().size() + 1, x, y);
        pins.emplace_back(p);
    }
    void rotate(int x);
    // returns id : starting point, rotation
    std::string toString();
    // returns Id and Pins coordinates
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    std::string toVisualLevelSting();
    friend bool operator<(const ElectronicComponent & e1,const ElectronicComponent & e2);
    friend bool operator==(const ElectronicComponent & e1,const ElectronicComponent & e2);
    friend bool operator!=(const ElectronicComponent & e1,const ElectronicComponent & e2);
};
#endif