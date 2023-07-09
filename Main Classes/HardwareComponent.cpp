#include "HardwareComponent.hpp"
const std::string HardwareComponent::NO_SUCH_ELECTRONIC_COMPONENT_ERROR{"There is no such electronic component"};
BoardFactory HardwareComponent:: boardFactory{};
ElectronicComponentFactory HardwareComponent:: ecFactory{};
HardwareComponent::HardwareComponent() : id{""}
{
}
HardwareComponent::HardwareComponent(std::string id, Board board, ElectronicComponentContainer components, ElectronicConnectionsContainer connections) :
id{id}, board{boardFactory.getInstance(board)}, components{components}, connections{connections}
{
}
std::string HardwareComponent::getId() const
{
    return this->id;
};
HardwareComponent::ElectronicComponentContainer HardwareComponent::getComponents() const
{
    return this->components;
}
HardwareComponent::ElectronicConnectionsContainer HardwareComponent::getConnections() const
{
    return this->connections;
}
const Board &HardwareComponent::getBoard() const
{
    return board;
}
const ElectronicComponent & HardwareComponent::getElectronicComponentByBoardNumber(int wanted)
{
     for (auto & ec: getComponents())
    {
        if ((ec).getBoardOrderNumber() == wanted)
        {
            return ec;
        }
    }
    throw std::invalid_argument(NO_SUCH_ELECTRONIC_COMPONENT_ERROR);
}
 void HardwareComponent::setBoard(Board board)
 { 
     this->board = board;
 }

std::string HardwareComponent::toDecsriptionFormatSting()
{
    std::string result{""};
    result.append("id: ").append(this->id).append("\n").append("width: ").append(std::to_string(this->getBoard().getWidth())).append("\n").append("height: ").append(std::to_string(this->getBoard().getHeight())).append("\n").append("components: ").append("\n");
    for (HardwareComponent::ElectronicComponentFactoryType & component : getComponents())
    {
        result.append((component).toString()).append("\n");
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
        for (HardwareComponent::ElectronicComponentFactoryType & component : getComponents())
        {
            componentStringMap[(component).getId()] = pair;
            componentStringMap[(component).getId()].first++;
            componentStringMap[(component).getId()].second.append((component).getStartingPosition().toMachineLevelFormatString())
                                                        .append(" ").append(std::to_string((component).getRotation()));
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

// std::string HardwareComponent::serialize()
// {
//     std::string result{""};
//     result.append(getId()).append(" ").append(getBoard().serialize()).append(" ").append(std::to_string(getComponents().size()));
//     for (HardwareComponent::ElectronicComponentFactoryType & c : getComponents())
//     {
//         result.append((*c).serialize()).append(" ");
//     }
//     result.append(std::to_string(getConnections().size())).append(" ");
//     for (ElectronicConnection connection : getConnections())
//     {
//         //result.append(connection.serialize()).append(" ");
//     }
//     return result;
// }
// HardwareComponent HardwareComponent::deserialize(std::stringstream & strm)
// {
//     std::string newId{""};
//     Board b;
//     int numberOfComponents{0};
//     HardwareComponent::ElectronicComponentContainer newComponents;
//     int numberOfConnections{0};
//     std::vector<ElectronicConnection> newConnections;
//     strm>>newId;
//     b = b.deserialize(strm);
//     b = boardFactory.getInstance(b);
//     for (size_t i = 0; i < numberOfComponents; i++)
//     {
//         ElectronicComponent eComp;
//         eComp = eComp.deserialize(strm);
//         newComponents.push_back(ecFactory.getInstancePointer(eComp));
//     }
    
//     for (size_t i = 0; i < numberOfConnections; i++)
//     {
//         ElectronicConnection eConn;
//         //eConn = eConn.deserialize(strm);
//         newConnections.push_back(eConn);
//     }

//     HardwareComponent result{newId, b, newComponents, newConnections};
//     return result;

// }


bool operator<(const HardwareComponent &h1, const HardwareComponent &h2) 
{
    return h1.getId() < h2.getId();
}

bool operator==(const HardwareComponent &h1, const HardwareComponent &h2)
{
    if (h1.getComponents().size() != h2.getComponents().size() 
        || h1.getConnections().size() != h2.getConnections().size() )
    {
        return false;
    }
    HardwareComponent::ElectronicComponentContainer  h1SortedComponents = h1.getComponents();
    HardwareComponent::ElectronicComponentContainer  h2SortedComponents = h2.getComponents();
    HardwareComponent::ElectronicConnectionsContainer h1SortedConnections = h1.getConnections();
    HardwareComponent::ElectronicConnectionsContainer h2SortedConnections = h2.getConnections();
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

std::ostream& operator<<(std::ostream & stream, const HardwareComponent& hc)
{
    stream << hc.id << ' ' << hc.board << ' ' << hc.components.size()  << ' ';
    for (size_t i = 0; i < hc.components.size(); i++)
    {
        stream<< hc.components[i]  << ' ';
    }
    
    stream << hc.connections.size() << ' ';

    for (size_t i = 0; i < hc.connections.size(); i++)
    {
     stream << hc.connections[i] << ' ';
    }
    stream << '\n';
    return stream;
}
std::istream& operator>>(std::istream & stream, HardwareComponent& hc)
{
    size_t containerSize{0};
        stream >> hc.id >> hc.board >> containerSize ;
    for (size_t i = 0; i < containerSize; i++)
    {
        hc.components.emplace_back(ElectronicComponent(stream));
    }
    
    stream >> containerSize;

    for (size_t i = 0; i < containerSize; i++)
    {
        hc.connections.emplace_back(ElectronicConnection(stream));
    }
    return stream;
}
