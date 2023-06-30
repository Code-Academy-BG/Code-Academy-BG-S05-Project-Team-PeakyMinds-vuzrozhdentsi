#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
class Board
{
    private:
    std::string id;
    int height;
    int width;

    public:
    Board(std::string id ="", int height = 0, int width = 0);
    int getHeight() const;
    int getWidth() const;
    void setHeight(int height);
    void setWidth(int width);
    std::string getId() const;
    std::string serialize() const;
    Board deserialize(std::stringstream & strm);
    friend bool operator<(const Board & b1, const Board & b2);
    friend bool operator==(const Board & b1, const Board & b2);
    friend bool operator!=(const Board & b1, const Board & b2);
    
    void printBoard()
    {
        std::cout<<"\nBoard ID:"<<id;
        for (int i=0; i<height; i++)
        {
            std::cout<<'\n';
            for (int j=0; j<width; j++)
            {
                std::cout<<'*';
            }
        }
    }

};

#endif