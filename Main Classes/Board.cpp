#include <string>
class Board
{
    private:
    std::string id = "";
    int height = 0;
    int width = 0;

    public:
    Board(std::string id, int height = 0, int width = 0) : id(id), height(height), width(width)
    {}
};