#include <string>
#include <vector>

struct Point
{
    private:
    int x = 0;
    int y = 0;

    public:
    Point(int x, int y) : x(x), y(y)
    {}
};

struct Pin
{
    private:
    std::string id;
    Point pinPos = Point(0,0);

    public:
    Pin(std::string id) : id(id)
    {}
};

enum Rotation
{
    Zero = 0,
    StraightAngle = 90,
    UTurn = 180,
    ThreeQuarters = 270
};

class ElectronicComponent
{
    private:
    std::string id = "";
    int height = 0;
    int width = 0;
    Rotation rotation = Rotation::Zero;
    std::vector<Pin> pins = {};
    Point startingPosition;

    public:
    ElectronicComponent(std::string id, int height, int width, Rotation rotation, std::vector<Pin> pins, Point startingPosition) : id(id), height(height), 
    width(width), rotation(rotation), pins(pins), startingPosition(startingPosition)
    {}
};