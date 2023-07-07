#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
class Board
{
    private:
    int width;
    int height;
    int id;

    public:
    Board(): width{0}, height{0}, id{0} {};
    Board(int width, int height);
    Board(std::istream& stream)
    {
        stream >> *this;
    }
    int getHeight() const;
    int getWidth() const;
    void setHeight(int height);
    void setWidth(int width);
    int setId(int w, int h);
    int getId() const;
    // std::string serialize() const;
    // Board deserialize(std::stringstream & strm);
    friend bool operator<(const Board & b1, const Board & b2);
    friend bool operator==(const Board & b1, const Board & b2);
    friend bool operator!=(const Board & b1, const Board & b2);
    friend std::ostream& operator<<(std::ostream & stream, const Board& b)
    {
            stream<<b.width<<' ' <<b.height<<' ';
            return stream;
    }
    friend std::istream& operator>>(std::istream & stream, Board& b)
    {
        stream >> b.width>>b.height;
        b.setId(b.width, b.height);
        return stream;
    }

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