#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "ElectronicComponent.hpp"
#include "ElectronicConnection.hpp"
#include "ElectronicComponentFactory.hpp"
#include "Board.hpp"
#include "BoardFactory.hpp"
#include <algorithm>

class HardwareComponent
{
public:
    // using PinFactoryRawMaterial = PinFactory::FactoryRawMaterial;
    // using PinFactoryType = PinFactory::FactoryType;
    // using PointFactoryRawMaterial = PointFactory::FactoryRawMaterial;
    // using PointFactoryType = PointFactory::FactoryType;
    using HCID = std::string;
    // using PinContainer = std::vector<PinFactoryType>;
    using ElectronicComponentFactoryType = ElectronicComponent; //ElectronicComponentFactory::FactoryType;
    using ElectronicComponentContainer = std::vector<ElectronicComponentFactoryType>;
    using ElectronicConnectionsContainer = std::vector<ElectronicConnection>;
private:
    static BoardFactory boardFactory;
    static ElectronicComponentFactory ecFactory;
    static const std::string NO_SUCH_ELECTRONIC_COMPONENT_ERROR;
    HCID id;
    Board board;
    ElectronicComponentContainer components;
    ElectronicConnectionsContainer connections;

public:
    HardwareComponent();
    HardwareComponent(const std::string& id,const Board & board, ElectronicComponentContainer components, ElectronicConnectionsContainer connections);
    HardwareComponent(std::istream& stream)
    {
        stream >> *this;
    };
    HCID getId() const;
    ElectronicComponentContainer getComponents() const;
    ElectronicConnectionsContainer getConnections() const;
    const Board & getBoard() const;
    ElectronicComponent & getElectronicComponentByBoardNumber(int wanted);
    void setBoard(const Board& board);
    void setId(const std::string& newId);
    // TODO review
    std::string toDecsriptionFormatSting();

    // TODO review
    std::string toMachineLevelFormatSting();
    
    // std::string toVisualLevelSting();
    // std::string serialize();
    // HardwareComponent deserialize(std::stringstream & strm);


    //HardwareComponent *getById(const std::string &id);
    void addElectronicComponent(ElectronicComponent & e,const  Point& p, int rotationQuadrant)
    {
        e.rotateThePins(rotationQuadrant-1);
        e.setBoardOrderNumber(this->getComponents().size() + 1);
        e.setStartingPosition(p);
        components.push_back(e);
    } 
     void addConnection(const ElectronicConnection& eCon)
     {
        connections.emplace_back(ElectronicConnection(eCon));
     }
    //bool equals(const HardwareComponent &h);
    //std::string toDecsriptionFormatSting();
    //std::string toMachineLevelFormatSting();
    // std::string toVisualLevelSting();
    // std::string serialize();
    // HardwareComponent * deserialize(const std::string & line);
    
    //compares IDs, used for set container 
    friend bool operator<(const HardwareComponent &h1, const HardwareComponent &h2);

    // compares physical requirements, not IDs
    friend bool operator==(const HardwareComponent &h1, const HardwareComponent &h2);
    
    // compares physical requirements, not IDs
    friend bool operator!=(const HardwareComponent &h1, const HardwareComponent &h2);
   
    friend std::ostream& operator<<(std::ostream & stream, const HardwareComponent& hc);
   
    friend std::istream& operator>>(std::istream & stream, HardwareComponent& hc);
};
#endif

