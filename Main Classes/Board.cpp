#include "Board.hpp"

Board::Board(int width, int height) : width{width}, height {height}, id{setId(width, height)} 
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
int Board::setId(int w, int h)
{
    int res{1};
    while (res < w || res < h)
    {
        res *=2;
    }
    return res;
}
void Board::setHeight(int height)
{
  this->height = height;

}
void Board::setWidth(int width)
{
  this->width = width;
}
int Board::getId() const
{
    return this->id;
}
// std::string Board::serialize() const
// {
//     std::string result{""};
//     result.append(getId()).append(" ").append(std::to_string(getHeight()))
//         .append(" ").append(std::to_string(getWidth()));
//     return result;    
// }
// Board Board::deserialize(std::stringstream & strm)
// {
//     std::string id {""};
//     std::string strH {""};
//     std::string strW {""};
//     strm >> id >> strH >> strW;
//     Board b(id,std::stoi(strH), std::stoi(strW));
//     return b;
// }
// returns true if the 2 sides are smaller OR the area is smaller
bool operator<(const Board &b1, const Board &b2)
{
    return (b1.getHeight() < b2.getHeight() && b1.getWidth() < b2.getWidth()) || (b1.getHeight() * b1.getWidth() < b2.getHeight() * b2.getWidth());
}
bool operator==(const Board &b1, const Board &b2)
{
    return (b1.getHeight() == b2.getHeight() && b1.getWidth() == b2.getWidth());
}
bool operator!=(const Board &b1, const Board &b2)
{
    return !(b1 == b2);
}
