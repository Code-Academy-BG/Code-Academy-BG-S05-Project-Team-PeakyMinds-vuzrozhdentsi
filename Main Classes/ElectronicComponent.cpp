#include "ElectronicComponent.hpp"
#include <string>
#include <vector>
     PinFactory ElectronicComponent::pinFactory {};
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
ElectronicComponent::Rotation ElectronicComponent::getRotationByQuadrant(int x) const
{
    switch (x)
    {
    case 1:
        return ElectronicComponent::Rotation::Zero;
        break;
    case 2:
        return ElectronicComponent::Rotation::StraightAngle;
        break;
    case 3 :
        return ElectronicComponent::Rotation::UTurn;
        break;
    case 4:
        return ElectronicComponent::Rotation::ThreeQuarters;
        break;
    // Exception to be thrown
    }
}
Pin* ElectronicComponent:: getPinById(int wantedId)
{
    for (auto & pointerToPin: getPins())
    {
        if ((*pointerToPin).getId() == wantedId)
        {
            return pointerToPin.get();
        }
    }
    return nullptr;
}
ElectronicComponent* ElectronicComponent::getElectronicComponentByBoardNumber(int wantedBoardNumber)
{
    if (wantedBoardNumber == getBoardOrderNumber())
    {
        return this;
    }
    return nullptr;
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
    for (auto & pointerToPin : getPins())
    {
        int newX{0}, newY{0};
        newX = (*pointerToPin).getPoint().getX() + xValDifference;
        newY = (*pointerToPin).getPoint().getY() + yValDifference;
        Pin p{(*pointerToPin).getId(), newX, newY};
        pointerToPin = pinFactory.getInstancePointer(p);
    }
    startingPosition = Pin::factory.getInstancePointer(point);
}
/* void ElectronicComponent::rotate(int x)
{
} */
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
    for (auto & pointerToPin : getPins())
    {
        result.append((*pointerToPin).toString()).append(",");
    }
    result.pop_back();
    return result;
}
std::string ElectronicComponent::toMachineLevelFormatSting()
{
    std::string result{""};
    result.append(getId()).append(": ").append(widthAndHeightToMachineLevelFormat());
    for (auto & pointerToPin : getPins())
    {
        result.append((*pointerToPin).toMachineLevelFormatString()).append(" ");
    }
    return result;
}
std::string ElectronicComponent::toVisualLevelSting()
{
    std::string result{""};
    return result;
}
std::string ElectronicComponent::widthAndHeightToMachineLevelFormat(int bits)
{
    unsigned long res{0};
    res |= this->getHeight();
    res <<= bits;
    res |= this->getWidth();
    return std::to_string(res);
}
std::string ElectronicComponent::serialize() const
{
    std::string result{""};
    result.append(getId()).append(" ").append(std::to_string(getHeight())).append(" ").append(std::to_string(getWidth()))
    .append(" ").append(std::to_string(getBoardOrderNumber())).append(" ").append(std::to_string(getRotation()))
    .append(" ").append((*startingPosition).serialize()).append(" ").append(std::to_string(getPins().size())).append(" ");
    for (auto & pointerToPin : getPins())
    {
        result.append((*pointerToPin).serialize()).append(" ");
    }
    return result;
}
ElectronicComponent ElectronicComponent::deserialize(std::stringstream & strm)
{
    std::string newId{""};
    std::string temp{""};
    int newHeight{0};
    int newWidth{0};
    int newBoardOrderNumber{0};
    ElectronicComponent::Rotation newRotation;
    Point newStartingPosition;
    int numberOfPins{0};
    std::vector<Pin> newPins;
    strm>>newId>>temp;
    newHeight = std::stoi(temp);
    temp.clear();
    strm>>temp;
    newWidth= std::stoi(temp);
    temp.clear();
    strm>>temp;
    newBoardOrderNumber= std::stoi(temp);
    temp.clear();
    strm>>temp;
    newRotation = getRotationByQuadrant(std::stoi(temp));
    temp.clear();
    strm>>temp;
    newStartingPosition = newStartingPosition.deserialize(strm);
    numberOfPins = std::stoi(temp);
    
    for (size_t i = 0; i < numberOfPins; i++)
    {
        Pin p;
        p = p.deserialize(strm);
        newPins.push_back(p);
    }
    
    ElectronicComponent result{newId, newHeight, newWidth, newBoardOrderNumber, newStartingPosition, newRotation, pins};
    return result;
}

bool operator<(const ElectronicComponent &e1, const ElectronicComponent &e2)
{
    ElectronicComponent::PinContainer e1SortedPins = e1.getPins();
    ElectronicComponent::PinContainer e2SortedPins = e2.getPins();
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
    ElectronicComponent::PinContainer e1SortedPins = e1.getPins();
    ElectronicComponent::PinContainer e2SortedPins = e2.getPins();
    std::sort(e1SortedPins.begin(), e1SortedPins.end());
    std::sort(e2SortedPins.begin(), e2SortedPins.end());
    return e1.getHeight() == e2.getHeight() && e1.getWidth() == e2.getWidth() && e1SortedPins == e2SortedPins;
}
bool operator!=(const ElectronicComponent &e1, const ElectronicComponent &e2)
{
    return !(e1 == e2);
}