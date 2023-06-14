#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include<string>
#include<vector>
#include "ElectronicComponent.hpp"
#include "ElectronicConnection.hpp"
#include "Board.hpp"
class HardwareComponent
{
private:
    std::string id;
    Board board;
    std::vector<ElectronicComponent> components;
    std::vector<ElectronicConnection> connections;
public:
    HardwareComponent();
    void addElectronicComponent(ElectronicComponent e, Point p);
     
    bool equals (HardwareComponent h);
    std::string toDecsriptionFormatSting();
    std::string toMachineLevelFormatSting();
    std::string toVisualLevelSting();
    std::string serialize(HardwareComponent h);
    HardwareComponent * deserialize(const std::string & line);

};
#endif