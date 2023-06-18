#include "HardwareComponent.hpp"

    HardwareComponent::HardwareComponent() : id{""}
    {
    };
    const std::string HardwareComponent::getId() const
    {
        return this->id;
    };
    std::set<ElectronicComponent> HardwareComponent::getComponents() const
    {
        return this->components;
    }
    std::set<ElectronicConnection> HardwareComponent::getConnections() const
    {
        return this->connections;
    }
    Board & HardwareComponent::getBoard()
    {
        return this->board;
    }
    HardwareComponent * HardwareComponent::getById(const std::string & requiredID)
    {
        if(this->id == requiredID){
            return this;
        }
        return nullptr;
    }
    void HardwareComponent::addElectronicComponent(ElectronicComponent e, Point p, int rotationQuadrant)
    {
        e.rotate(rotationQuadrant);
        // if empty size is 0, so 1 is added prior changing the size
        e.setBoardOrderNumber(this->getComponents().size()+1);
        //... imprints the EC on the Board
    }
    bool HardwareComponent::equals (const HardwareComponent & h)
    {
        return *this == h;
    }
    std::string HardwareComponent::toDecsriptionFormatSting()
    {
        std::string result{""};
        result.append("id: ").append(this->id).append("\n")
            .append("width: ").append(std::to_string(this->getBoard().getWidth())).append("\n")
            .append("height: ").append(std::to_string(this->getBoard().getHeight())).append("\n")
            .append("components: ").append("\n");
            for(auto component : getComponents())
            {
                result.append(component.toString()).append("\n");
            }
            result.append("connections: ");
            for(auto connection : getConnections())
            {
                result.append(connection.toString()).append(", ");
            }
        return result;
    }
    std::string HardwareComponent::toMachineLevelFormatSting()
    {
        std::string result{""};
        result.append(getId()).append(": \n");
        // mapping components
        std::map<std::string, std::pair<int, std::string>>  componentStringMap;
        int counter = 0;
        std::string stringRepresentation{""};
        std::pair<int, std::string> pair;
        pair.first = counter;
        pair.second = stringRepresentation;
        for (auto component : getComponents())
        {
            componentStringMap[component.getId()] = pair;
            componentStringMap[component.getId()].first++;
            componentStringMap[component.getId()].second 
            += component.getStartingPosition()->toMachineLevelFormatString() 
            + " " + component.getRotation(); 
        }
        // adding the mappind to the final result, first component ID, then the amount in the hardware component and for each starting position and rotation
        for(auto mapling : componentStringMap)
        {
            result.append(mapling.first).append(": ")
            .append(std::to_string(mapling.second.first))
            .append(mapling.second.second);
        }
        //  adding possitions of connections
        result.append("\n");
        for(auto connection : getConnections())
        {
            result.append(connection.toMachineLevelFormatSting()).append(" ");
        }
        
       
        
        return result;
    }
    std::string HardwareComponent::toVisualLevelSting()
    {
    }
    std::string HardwareComponent::serialize()
    {
    }
    HardwareComponent * HardwareComponent::deserialize(const std::string & line)
    {
    }
    bool HardwareComponent::operator<(const HardwareComponent & h) const
    {
    }
    bool HardwareComponent::operator==(const HardwareComponent & h) const
    {
        return this->getComponents().size() == h.getComponents().size()
            && this->getConnections().size() == h.getConnections().size()
            && this->getComponents() == h.getComponents()
            && this->getConnections() == h.getConnections();  
    }
    bool HardwareComponent::operator!=(const HardwareComponent & h) const
    {
        return !(*this == h);
    }
