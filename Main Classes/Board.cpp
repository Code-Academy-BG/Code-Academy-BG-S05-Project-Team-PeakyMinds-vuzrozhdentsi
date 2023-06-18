#include "Board.hpp"

Board::Board(std::string id, int height = 0, int width = 0) : id(id), height(height), width(width)
{
}
int Board::getHeight() const
{
    return this->height;
}
int Board::getWidth() const
{
    return this->width;
}
const std::string Board::getId() const
{
    return this->id;
}
// returns true if the 2 sides are smaller OR the area is smaller
bool Board::operator<(const Board &b) const
{
    return (this->height < b.height && this->width < b.width) || (this->height * this->width < b.height * b.width);
}
bool Board::operator==(const Board &b) const
{
    return (this->height == b.height && this->width == b.width);
}
bool Board::operator!=(const Board &b) const
{
    return !(*this == b);
}
