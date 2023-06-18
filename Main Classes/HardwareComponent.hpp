#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include<string>
#include<set>
#include <map>
#include "ElectronicComponent.hpp"
#include "ElectronicConnection.hpp"
#include "Board.hpp"
#include <algorithm>
class HardwareComponent
{
private:
    std::string id;
    Board board;
    std::set<ElectronicComponent> components;
    std::set<ElectronicConnection> connections;
public:
    HardwareComponent();
    const std::string getId() const;
    std::set<ElectronicComponent> getComponents() const;
    std::set<ElectronicConnection> getConnections() const;
    Board & getBoard();
    HardwareComponent * getById(const std::string & id);
    void addElectronicComponent(ElectronicComponent e, Point p, int rotationQuadrant);  
    bool equals (const HardwareComponent & h);
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    std::string toVisualLevelSting();
    std::string serialize();
    HardwareComponent * deserialize(const std::string & line);
    bool operator<(const HardwareComponent & h) const;
    bool operator==(const HardwareComponent & h) const;
    bool operator!=(const HardwareComponent & h) const;
};
#endif
