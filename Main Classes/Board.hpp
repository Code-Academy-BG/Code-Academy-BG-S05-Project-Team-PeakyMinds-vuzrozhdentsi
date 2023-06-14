#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board
{
    private:
    std::string id;
    int height;
    int width;

    public:
    Board(std::string id ="", int height = 0, int width = 0);
};

#endif