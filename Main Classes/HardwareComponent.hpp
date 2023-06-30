#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "ElectronicComponent.hpp"
#include "ElectronicConnection.hpp"
#include "Board.hpp"
#include <algorithm>

class HardwareComponent
{
private:
    std::string id;
    Board board;
    std::vector<ElectronicComponent> components;
    std::vector<ElectronicConnection> connections;

public:
    HardwareComponent();
    HardwareComponent(std::string id, Board board, std::vector<ElectronicComponent> components, std::vector<ElectronicConnection> connections);
    std::string getId() const;
    std::vector<ElectronicComponent> getComponents() const;
    std::vector<ElectronicConnection> getConnections() const;
    const Board & getBoard() const;
    void setBoard(Board board);
    HardwareComponent * getById(const std::string & id);
    void addElectronicComponent(ElectronicComponent e, Point p, int rotationQuadrant);  
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
