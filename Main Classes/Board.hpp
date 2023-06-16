#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <vector>
class Board
{
    private:
    std::string id;
    int height;
    int width;

    public:
<<<<<<< Updated upstream
    Board(std::string id ="", int height = 0, int width = 0);
    int getHeight() const;
    int getWidth() const;
    const std::string getId() const;
    bool operator<(const Board & b) const;
    bool operator==(const Board & b) const;
    bool operator!=(const Board & b) const;
=======
    Board(std::string id ="", int height = 0, int width = 0) 
    : id(id), height(height), width(width)
    {}

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

>>>>>>> Stashed changes
};

#endif