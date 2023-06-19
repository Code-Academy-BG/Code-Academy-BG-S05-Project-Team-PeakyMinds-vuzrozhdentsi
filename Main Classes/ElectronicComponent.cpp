#include "ElectronicComponent.hpp"
#include <string>
#include <vector>

int ElectronicComponent::getRotation() const
{
    switch (this->rotation)
    {
    case ElectronicComponent::Rotation::Zero:
        return 1;
        break;
    case ElectronicComponent::Rotation::StraightAngle:
        return 2;
        break;
    case ElectronicComponent::Rotation::UTurn:
        return 3;
        break;
    case ElectronicComponent::Rotation::ThreeQuarters:
        return 4;
        break;
    default:
        return -1;
        break;
    }
}
void ElectronicComponent::setRotation(int quadrantNumber)
{
    switch (quadrantNumber)
    {
    case 1:
        this->rotation = ElectronicComponent::Rotation::Zero;
        break;
    case 2:
        this->rotation = ElectronicComponent::Rotation::StraightAngle;
        break;
    case 3:
        this->rotation = ElectronicComponent::Rotation::UTurn;
        break;
    case 4:
        this->rotation = ElectronicComponent::Rotation::ThreeQuarters;
        break;
    default:
        break;
    }
}
void ElectronicComponent::setStartingPosition(Point point)
{
    int xValDifference{0};
    int yValDifference{0};
    xValDifference = point.getX() - this->getStartingPosition().getX();
    yValDifference = point.getY() - this->getStartingPosition().getY();
    for (Pin &pin : getPins())
    {
        int newX{0}, newY{0};
        newX = pin.getPoint().getX() + xValDifference;
        newY = pin.getPoint().getY() + yValDifference;
        pin.setPosition(newX, newY);
    }
    startingPosition.set(point.getX(), point.getY());
}
void ElectronicComponent::rotate(int x)
{
}
std::string ElectronicComponent::toString()
{
    std::string result{""};
    result.append(getId()).append(": ").append(getStartingPosition().toString()).append(",").append(std::to_string(getRotation()));
    return result;
}
std::string ElectronicComponent::toDecsriptionFormatSting()
{
    std::string result{""};
    result.append("id: ").append(getId()).append("\n").append("width: ").append(std::to_string(getWidth())).append("\n").append("height: ").append(std::to_string(getHeight())).append("\n").append("pins: ");
    for (Pin &pin : getPins())
    {
        result.append(pin.toString()).append(",");
    }
    result.pop_back();
    return result;
}
std::string ElectronicComponent::toMachineLevelFormatSting()
{
    std::string result{""};
    result.append(getId()).append(": ").append(widthAndHeightToMachineLevelFormat());
    for (Pin &pin : getPins())
    {
        result.append(pin.toMachineLevelFormatString()).append(" ");
    }
}
std::string ElectronicComponent::toVisualLevelSting()
{
}
std::string ElectronicComponent::widthAndHeightToMachineLevelFormat(int bits)
{
    unsigned long res{0};
    res |= this->getHeight();
    res <<= bits;
    res |= this->getWidth();
    return std::to_string(res);
}

bool operator<(const ElectronicComponent &e1, const ElectronicComponent &e2)
{
    std::vector<Pin> e1SortedPins = e1.getPins();
    std::vector<Pin> e2SortedPins = e2.getPins();
    std::sort(e1SortedPins.begin(), e1SortedPins.end());
    std::sort(e2SortedPins.begin(), e2SortedPins.end());

    if ((e1.getHeight() < e2.getHeight() && e1.getWidth() < e2.getWidth()) || (e1.getHeight() * e1.getWidth() < e2.getHeight() * e2.getWidth()))
    {
        return true;
    }
    else
    {
        if (e1SortedPins.size() < e2SortedPins.size())
        {
            return true;
        }
        else
        {
            if (e1SortedPins < e2SortedPins)
            {
                return true;
            }
        }
    }
    return false;
}

bool operator==(const ElectronicComponent &e1, const ElectronicComponent &e2)
{
    if (e1.getPins().size() != e2.getPins().size())
    {
        return false;
    }
    std::vector<Pin> e1SortedPins = e1.getPins();
    std::vector<Pin> e2SortedPins = e2.getPins();
    std::sort(e1SortedPins.begin(), e1SortedPins.end());
    std::sort(e2SortedPins.begin(), e2SortedPins.end());
    return e1.getHeight() == e2.getHeight() && e1.getWidth() == e2.getWidth() && e1SortedPins == e2SortedPins;
}
bool operator!=(const ElectronicComponent &e1, const ElectronicComponent &e2)
{
    return !(e1 == e2);
}