#ifndef ELECTRONICCOMPONENT_H
#define ELECTRONICCOMPONENT_H

#include <string>
#include<vector>
#include "Pin.hpp"

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

    public:
    ElectronicComponent(std::string id = "", int height = 0, int width = 0, int boardOrderNumber =0,
                         Rotation rotation = Rotation::Zero, Point startingPosition = (0,0),
                         std::vector<Pin> pins);

    void setBoardOrderNumber(int number);
    const int getBoardOrderNumber() const;
    void addPin(int x, int y); //this is the moment to Pin p.setid = vector index
    void rotate(int x); 
    std::string toString();
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    std::string toVisualLevelSting();

};
#endif