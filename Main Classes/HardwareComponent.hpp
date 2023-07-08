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
    using PinFactoryRawMaterial = PinFactory::FactoryRawMaterial;
    using PinFactoryType = PinFactory::FactoryType;
    using PointFactoryRawMaterial = PointFactory::FactoryRawMaterial;
    using PointFactoryType = PointFactory::FactoryType;
    using HCID = std::string;
    using PinContainer = std::vector<PinFactoryType>;
    using ElectronicComponentFactoryType = ElectronicComponentFactory::FactoryType;
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
    HardwareComponent(HCID id, Board board, ElectronicComponentContainer components, ElectronicConnectionsContainer connections);
    HardwareComponent(std::istream& stream)
    {
        stream >> *this;
    };
    HCID getId() const;
    ElectronicComponentContainer getComponents() const;
    ElectronicConnectionsContainer getConnections() const;
    const Board & getBoard() const;
    const ElectronicComponent & getElectronicComponentByBoardNumber(int wanted);
    // void setBoard(Board board);

    // TODO review
    std::string toDecsriptionFormatSting();

    // TODO review
    std::string toMachineLevelFormatSting();
    
    // std::string toVisualLevelSting();
    // std::string serialize();
    // HardwareComponent deserialize(std::stringstream & strm);

    //const Board &getBoard() const;
    //HardwareComponent *getById(const std::string &id);
    /* void addElectronicComponent(ElectronicComponent e, Point p, int rotationQuadrant)
    {
        e.rotate(rotationQuadrant);
        // if empty size is 0, so 1 is added prior changing the size
        e.setBoardOrderNumber(this->getComponents().size() + 1);
        //... imprints the EC on the Board
        e.setStartingPosition(p);
    } */
    // void addConnection();
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

