#include "HardwareComponent.hpp"

HardwareComponent::HardwareComponent() : id{""}
{
}
std::string HardwareComponent::getId() const
{
    return this->id;
};
std::vector<ElectronicComponent> HardwareComponent::getComponents() const
{
    return this->components;
}
std::vector<ElectronicConnection> HardwareComponent::getConnections() const
{
    return this->connections;
}
const Board &HardwareComponent::getBoard() const
{
    return this->board;
}
HardwareComponent *HardwareComponent::getById(const std::string &requiredID)
{
    if (this->id == requiredID)
    {
        return this;
    }
    return nullptr;
}
void HardwareComponent::addElectronicComponent(ElectronicComponent e, Point p, int rotationQuadrant)
{
    e.rotate(rotationQuadrant);
    // if empty size is 0, so 1 is added prior changing the size
    e.setBoardOrderNumber(this->getComponents().size() + 1);
    //... imprints the EC on the Board
    e.setStartingPosition(p);
}
bool HardwareComponent::equals(const HardwareComponent &h)
{
    return *this == h;
}
std::string HardwareComponent::toDecsriptionFormatSting()
{
    std::string result{""};
    result.append("id: ").append(this->id).append("\n").append("width: ").append(std::to_string(this->getBoard().getWidth())).append("\n").append("height: ").append(std::to_string(this->getBoard().getHeight())).append("\n").append("components: ").append("\n");
    for (ElectronicComponent & component : getComponents())
    {
        result.append(component.toString()).append("\n");
    }
    result.append("connections: ");
    for (ElectronicConnection & connection : getConnections())
    {
        result.append(connection.toString()).append(", ");
    }
    return result;
}
std::string HardwareComponent::toMachineLevelFormatSting()
{
    std::string result{""};
    // adding components
    result.append(getId()).append(": \n");
    if (!getComponents().empty())
    {
        // mapping components
        std::map<std::string, std::pair<int, std::string>> componentStringMap;
        int counter = 0;
        std::string stringRepresentation{""};
        std::pair<int, std::string> pair;
        pair.first = counter;
        pair.second = stringRepresentation;
        for (ElectronicComponent & component : getComponents())
        {
            componentStringMap[component.getId()] = pair;
            componentStringMap[component.getId()].first++;
            componentStringMap[component.getId()].second.append(component.getStartingPosition().toMachineLevelFormatString())
                                                        .append(" ").append(std::to_string(component.getRotation()));
        }

        // adding the mapping to the final result, first component ID, then the amount in the hardware component and for each starting position and rotation
        for (auto mapling : componentStringMap)
        {
            result.append(mapling.first).append(": ").append(std::to_string(mapling.second.first)).append(mapling.second.second);
        }
    }

    //  adding positions of connections
    result.append("\n");
    if (!getConnections().empty())
    {
        for (auto connection : getConnections())
        {
            result.append(connection.toMachineLevelFormatSting()).append(" ");
        }
    }

    return result;
}
// std::string HardwareComponent::toVisualLevelSting()
// {
// }
// std::string HardwareComponent::serialize()
// {
// }
// HardwareComponent *HardwareComponent::deserialize(const std::string &line)
// {
// }
bool operator<(const HardwareComponent &h1, const HardwareComponent &h2) 
{
    std::vector <ElectronicComponent> h1SortedComponents = h1.getComponents();
    std::vector <ElectronicComponent> h2SortedComponents = h2.getComponents();
    std::vector <ElectronicConnection> h1SortedConnections = h1.getConnections();
    std::vector <ElectronicConnection> h2SortedConnections = h2.getConnections();
    if (h1.getBoard() < h2.getBoard())
    {
        return true;
    }
    else if (h1.getBoard() == h2.getBoard())
    {
        if (h1SortedComponents.size() < h2SortedComponents.size())
        {
            return true;
        }
        else if (h1SortedComponents.size() == h2SortedComponents.size())
        {
            if (h2SortedConnections.size() < h2SortedConnections.size())
            {
                return true;
            }
        }
    }
    return false;
}
bool operator==(const HardwareComponent &h1, const HardwareComponent &h2)
{
    if (h1.getComponents().size() != h2.getComponents().size() 
        || h1.getConnections().size() != h2.getConnections().size() )
    {
        return false;
    }
    std::vector <ElectronicComponent> h1SortedComponents = h1.getComponents();
    std::vector <ElectronicComponent> h2SortedComponents = h2.getComponents();
    std::vector <ElectronicConnection> h1SortedConnections = h1.getConnections();
    std::vector <ElectronicConnection> h2SortedConnections = h2.getConnections();
    std::sort(h1SortedComponents.begin(),h1SortedComponents.end());
    std::sort(h2SortedComponents.begin(),h2SortedComponents.end());
    std::sort(h1SortedConnections.begin(),h1SortedConnections.end());
    std::sort(h2SortedConnections.begin(),h2SortedConnections.end());
    return h1.getBoard() == h2.getBoard()
        && h1SortedComponents == h2SortedComponents 
        && h1SortedConnections == h2SortedConnections;
}
bool operator!=(const HardwareComponent &h1, const HardwareComponent &h2)
{
    return !(h1 == h2);
}
