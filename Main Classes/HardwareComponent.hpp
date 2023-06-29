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
private:
    static BoardFactory boardFactory;
    static ElectronicComponentFactory ecFactory;
    HCID id;
    Board board;
    ElectronicComponentContainer components;
    std::vector<ElectronicConnection> connections;

public:
    HardwareComponent();
    HardwareComponent(HCID id, Board board, ElectronicComponentContainer components, std::vector<ElectronicConnection> connections);
    HCID getId() const;
    ElectronicComponentContainer getComponents() const;
    std::vector<ElectronicConnection> getConnections() const;
    const Board & getBoard() const;
    HardwareComponent * getById(const std::string & id);
    void addElectronicComponent(ElectronicComponent* e, Point* p, int rotationQuadrant);  
    void addConnection(ElectronicComponent e1,Pin p1, ElectronicComponent e2, Pin p2);
    bool equals (const HardwareComponent & h);
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    // std::string toVisualLevelSting();
    std::string serialize();
    HardwareComponent deserialize(std::stringstream & strm);
    friend bool operator<(const HardwareComponent & h1,const HardwareComponent & h2);
    friend bool operator==(const HardwareComponent & h1,const HardwareComponent & h2);
    friend bool operator!=(const HardwareComponent & h1,const HardwareComponent & h2);
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
    friend bool operator<(const HardwareComponent &h1, const HardwareComponent &h2);
    friend bool operator==(const HardwareComponent &h1, const HardwareComponent &h2);
    friend bool operator!=(const HardwareComponent &h1, const HardwareComponent &h2);
};
#endif
