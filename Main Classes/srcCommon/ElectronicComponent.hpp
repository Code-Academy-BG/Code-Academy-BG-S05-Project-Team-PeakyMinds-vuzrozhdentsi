#ifndef ELECTRONIC_COMPONENT_H
#define ELECTRONIC_COMPONENT_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include"PinFactory.hpp"
#include"PointFactory.hpp"
#include <iostream>
class ElectronicComponent
{

    enum class Rotation
    {
        Zero = 0,
        StraightAngle = 90,
        UTurn = 180,
        ThreeQuarters = 270
    };
public:

    using ECID = std::string;
    using PinContainer = std::vector<Pin>;


    
private:

    ECID id;
    int width;
    int height;
    int boardOrderNumber;
    Rotation rotation;
    Point startingPosition;
    std::vector<std::vector<int>> component = {};
    PinContainer pins;

private:
    static const std::string NO_SUCH_PIN_ERROR;
    static const unsigned int BIT8 = 8;
    std::string widthAndHeightToMachineLevelFormat(int bits = BIT8);

public:
    ElectronicComponent(const std::string& id = "", int width = 0, int height = 0, int boardOrderNumber = 0,
                        const Point& startingPosition = Point(0, 0), Rotation rotation = Rotation::Zero)
        : id{id}, width{width}, height{height}, boardOrderNumber{boardOrderNumber},
          startingPosition{startingPosition}, rotation{rotation}
    {
        // int counter = 1;
        for (int i = 0; i < height; ++i)
        {
            component.emplace_back(std::vector<int>(width,0));
        }
    }
    void printElComp()
    {

        std::cout << "\nEl. Component ID:" << id;
        for (int i = 0; i < height; ++i)
        {
            std::cout << '\n';
            for (int j = 0; j < width; ++j)
                std::cout << component[i][j];
        }
    }
    ElectronicComponent(const std::string& id, int width, int height, int boardOrderNumber,
                       const Point& startingPosition, Rotation rotation, PinContainer& pins)
        : id{id}, width{width}, height{height}, boardOrderNumber{boardOrderNumber},
          startingPosition{startingPosition}, rotation{rotation}, pins{pins}
    {
    }
    ElectronicComponent(std::istream& stream)
    {
        stream >> *this;
        buildComponentAnew();
        resetAllPins();
    }
    ECID getId() const
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
        return startingPosition;
    }
   
    int getRotation() const;
    Rotation getRotationByQuadrant(int x) const;
    int getBoardOrderNumber() const
    {
        return this->boardOrderNumber;
    }
    
    PinContainer getPins() const
    {
        return this->pins;
    }
    Pin& getPinById(int wantedId);
    void setStartingPosition(Point point);
    void setId(const std::string& newID);
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
        
        pins.push_back(p);
        component[y][x] = p.getId();
    }
    void addPin2(int x, int y) // this is the moment to Pin p.setid = vector index
    {
        Pin p(getPins().size() + 1, x, y);

        pins.emplace_back(p);
        //  component[y][x] = p.getId();
    }
    inline void resetAllPins()
    {
        for (auto iter = pins.begin(); iter != pins.end(); ++iter)
        {
            component[(*iter).getPoint().getY()][(*iter).getPoint().getX()] = (*iter).getId();
        }
    }
    inline void swapHeightAndWeight()
    {
        int temp = height;
        height = width;
        width = temp;
    }
    inline void buildComponentAnew()
    {
        component = {};
        for (int i = 0; i < height; ++i)
        {
            component.emplace_back(std::vector<int>(width,0));
        } 
    }
   
    void rotateThePins(int x)
    {
        if (x == static_cast<int>(Rotation::StraightAngle))
        {
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    if (component[i][j] != 0)
                    {
                        // std::cout<<'\n'<<'|'<<'['<<i<<']'<<'['<< j << ']'<<'='<<'['<<j<<']'<<'['<<height-i-1<<']';
                        // pin(j,i) -> pin(height-i-1,j)
                        for (auto iter = pins.begin(); iter != pins.end(); ++iter)
                        {
                            if ((*iter).getId() == component[i][j])
                            {
                                (*iter).setPosition(height - i - 1, j);
                                break;
                            }
                        }
                    }
                }
            }
            swapHeightAndWeight();
            buildComponentAnew();
        }

        else if (x == static_cast<int>(Rotation::UTurn)) // 180gradusa//tuka nqma nujda da prazni vektora, no za test
        {
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (component[i][j] != 0)
                        {
                             //std::cout<<'\n'<<'|'<<'['<<i<<']'<<'['<<j<<']'<<'='<<'['<< height-1-i<<']'<<'['<<width-j-1<<']'; 
                             //pin(j,i) -> pin(width-j-1,height-1-i)
                            for (auto iter = pins.begin(); iter != pins.end(); ++iter)
                            {
                                if ((*iter).getId() == component[i][j])
                                {
                                    (*iter).setPosition(width-j-1,height-1-i);
                                    break;
                                    //std::swap(component[i][j], component[height - 1 - i][width - j - 1]);
                                }
                            }
                        }
                        
                    }
                }
            buildComponentAnew();
        }

        else if (x == static_cast<int>(Rotation::ThreeQuarters))
        {
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    if (component[i][j] != 0)
                    {
                         //std::cout<<'\n'<<'|'<<'['<<i<<']'<<'['<< j << ']'<<'='<<'['<<width-j-1<<']'<<'['<<i<<']';
                        // pin(j,i) -> pin(i,width-j-1)
                        for (auto iter = pins.begin(); iter != pins.end(); ++iter)
                        {
                            if ((*iter).getId() == component[i][j])
                            {
                                (*iter).setPosition(i,width-j-1);
                                break;
                            }
                        }
                    }
                }
            }
            swapHeightAndWeight();
            buildComponentAnew();
        }
        resetAllPins();
    }

    
    
    // returns id : starting point, rotation
    // TODO delete
    std::string toString();
    
    // returns Id and Pins coordinates
    // TODO review
    std::string toDecsriptionFormatSting();
    // TODO review
    std::string toMachineLevelFormatSting();
    
    // compares IDs, used for set containers
    friend bool operator<(const ElectronicComponent &e1, const ElectronicComponent &e2);

    // compares physical requirements
    friend bool operator==(const ElectronicComponent &e1, const ElectronicComponent &e2);
    
    // compares physical requirements
    friend bool operator!=(const ElectronicComponent &e1, const ElectronicComponent &e2);

    friend std::istream& operator>>(std::istream& stream, ElectronicComponent & ec);
    
    friend std::ostream& operator<<(std::ostream& stream, const ElectronicComponent & ec);
};
#endif