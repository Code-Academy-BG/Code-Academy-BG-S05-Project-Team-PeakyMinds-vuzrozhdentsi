#ifndef ELECTRONIC_COMPONENT_H
#define ELECTRONIC_COMPONENT_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Pin.hpp"
#include "Point.hpp"
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

private:
    std::string id;
    int height;
    int width;
    std::vector<std::vector<int>> component = {};
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
        // int counter = 1;
        for (int i = 0; i < height; ++i)
        {
            std::vector<int> vec1;

            for (int j = 0; j < width; ++j)
            {
                /* vec1.emplace_back(counter);
                if (counter < 9)
                    ++counter;
                else
                    counter = 0; */
                vec1.emplace_back(0);
            }
            component.emplace_back(vec1);
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
    ElectronicComponent(std::string id, int height, int width, int boardOrderNumber,
                        Point startingPosition, Rotation rotation, std::vector<Pin> pins)
        : id{id}, height{height}, width{width}, boardOrderNumber{boardOrderNumber},
          startingPosition{startingPosition}, rotation{rotation}, pins{pins}
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
    Rotation getRotationByQuadrant(int x) const;
    int getBoardOrderNumber() const
    {
        return this->boardOrderNumber;
    }
    ElectronicComponent *getElectronicComponentByBoardNumber(int wantedBoardNumber);
    std::vector<Pin> getPins() const
    {
        return this->pins;
    }
    Pin *getPinById(int wantedId);
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
        component[y][x] = p.getId();
    }
    inline void resetAllPins()
    {
        for (auto iter = pins.begin(); iter != pins.end(); ++iter)
        {
            component[iter->getPoint().getY()][iter->getPoint().getX()] = iter->getId();
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
            std::vector<int> vec1;

            for (int j = 0; j < width; ++j)
            {
                vec1.emplace_back(0);
            }
            component.emplace_back(vec1);
        } 
    }
    void clearPinsFromComponent()//bugav
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (component[i][j] != 0)
                {
                    component[i][j] == 0;
                }
            }
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
                            if (iter->getId() == component[i][j])
                            {
                                iter->setPosition(height - i - 1, j);
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
                                if (iter->getId() == component[i][j])
                                {
                                    iter->setPosition(width-j-1,height-1-i);
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
                            if (iter->getId() == component[i][j])
                            {
                                iter->setPosition(i,width-j-1);
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

    int rotate(int x)
    {

        if (x == static_cast<int>(Rotation::StraightAngle)) // prav ugul
        {
            std::vector<std::vector<int>> rotatedVector = {};
            for (int i = 0; i < width; i++)
            {
                std::cout << "rotation";
                std::vector<int> vec1 = {};
                for (int j = height - 1; j >= 0; j--)
                {
                    std::cout << "\nmini rotation cycle";
                    vec1.push_back(component[j][i]);

                    std::cout << '[' << i << ']' << '[' << height - j - 1 << ']' << '=' << '[' << j << ']' << '[' << i << ']';
                }
                rotatedVector.push_back(vec1);
            }

            int temp = height;
            height = width;
            width = temp;
            component = rotatedVector;
        }

        else if (x == static_cast<int>(Rotation::UTurn)) // 180gradusa
        {
            std::cout << "\n180 gradusa!";
            if (height % 2 == 0)
            {
                for (int i = 0; i < height / 2; i++)
                {
                    std::cout << '\n';
                    // for (int j=width-1; j>=0; j--)
                    for (int j = 0; j < width; j++)
                    {
                        std::cout << ' ' << '[' << i << ']' << '[' << j << ']' << '=' << '[' << height - 1 - i << ']' << '[' << width - j - 1 << ']' << component[i][j] << '=' << component[height - 1 - i][width - j - 1];
                        std::swap(component[i][j], component[height - 1 - i][width - j - 1]);
                    }
                }
            }
            else
            {
                for (int i = 0; i <= height / 2; i++)
                {
                    std::cout << '\n';
                    // for (int j=width-1; j>=0; j--)
                    if (i == height / 2)
                    {
                        std::cout << "\nSreda dostignata! Tuka po-poleka";
                        for (int j = 0; j < width / 2; j++)
                        {
                            std::cout << ' ' << '[' << i << ']' << '[' << j << ']' << '=' << '[' << height - 1 - i << ']' << '[' << width - j - 1 << ']' << component[i][j] << '=' << component[height - 1 - i][width - j - 1];
                            std::swap(component[i][j], component[height - 1 - i][width - j - 1]);
                        }
                    }
                    else
                    {
                        for (int j = 0; j < width; j++)
                        {
                            std::cout << ' ' << '[' << i << ']' << '[' << j << ']' << '=' << '[' << height - 1 - i << ']' << '[' << width - j - 1 << ']' << component[i][j] << '=' << component[height - 1 - i][width - j - 1];
                            std::swap(component[i][j], component[height - 1 - i][width - j - 1]);
                        }
                    }
                }
            }
        }

        else if (x == static_cast<int>(Rotation::ThreeQuarters)) // prav ugul
        {
            std::vector<std::vector<int>> rotatedVector = {};
            for (int i = 0; i < width; i++)
            {
                std::cout << "\nrotation";
                std::vector<int> vec1 = {};
                for (int j = 0; j < height; j++)
                {
                    // std::cout << "\nmini rotation cycle";
                    vec1.push_back(component[j][width - i - 1]);

                    std::cout << ' ' << '[' << i << ']' << '[' << j << ']' << '=' << '[' << j << ']' << '[' << width - i - 1 << ']'; // << component[i][j] << '=' << component[height - 1 - i][width - j - 1];
                }
                rotatedVector.push_back(vec1);
            }

            int temp = height;
            height = width;
            width = temp;
            component = rotatedVector;
        }

        /* for (int i=0; i<height; i++)
        {
            std::cout<<'\n';
            for (int j=0; j<width; j++)
            {
                std::cout<<rotatedVector[i][j];
            }
        } */
        return 0;
    }
    // returns id : starting point, rotation
    std::string toString();
    // returns Id and Pins coordinates
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    std::string toVisualLevelSting();
    std::string serialize() const;
    ElectronicComponent deserialize(std::stringstream &strm);
    friend bool operator<(const ElectronicComponent &e1, const ElectronicComponent &e2);
    friend bool operator==(const ElectronicComponent &e1, const ElectronicComponent &e2);
    friend bool operator!=(const ElectronicComponent &e1, const ElectronicComponent &e2);
    friend bool operator<(const ElectronicComponent &e1, const ElectronicComponent &e2);
    friend bool operator==(const ElectronicComponent &e1, const ElectronicComponent &e2);
    friend bool operator!=(const ElectronicComponent &e1, const ElectronicComponent &e2);
};
#endif