#ifndef ELECTRONIC_CONNECTION_H
#define ELECTRONIC_CONNECTION_H

#include <string>
#include <sstream>
#include "ElectronicComponent.hpp"
#include "HardwareComponent.hpp"


class ElectronicConnection
{
private:
    std::pair<ElectronicComponent,ElectronicComponent> electronicComponentConnection;
    std::pair<Pin,Pin> pinConnection;
public:
    ElectronicConnection(): electronicComponentConnection{}, pinConnection{}{};
    ElectronicConnection(ElectronicComponent e1,Pin pin1,ElectronicComponent e2, Pin pin2)
    {
        electronicComponentConnection.first = e1;
        electronicComponentConnection.second = e2;
        pinConnection.first = pin1;
        pinConnection.second = pin2;
    }
    // void resetConnection(ElectronicComponent e1,int pinPosition1,ElectronicComponent e2, int pinPostion2);
    std::pair<Pin, Pin> getPinConnection() const {
         return this->pinConnection;
    }
    std::string toMachineLevelFormatSting()
    {
        std::string result{""};
        result.append(pinConnection.first.toMachineLevelFormatString()).append(" ").append(pinConnection.second.toMachineLevelFormatString());
        return result;
    };
    std::string toString(){
        std::string result{""};
        result.append("(") .append(std::to_string(electronicComponentConnection.first.getBoardOrderNumber())).append(".").append(std::to_string(pinConnection.first.getId()))
            .append(",") .append(std::to_string(electronicComponentConnection.second.getBoardOrderNumber())).append(".").append(std::to_string(pinConnection.second.getId()))
            .append(")");
        return result;
    }
    std::string serialize() const
    {
        std::string result{""};
        result.append(std::to_string(electronicComponentConnection.first.getBoardOrderNumber())).append(" ").append(std::to_string(pinConnection.first.getId()))
            .append(" ") .append(std::to_string(electronicComponentConnection.second.getBoardOrderNumber())).append(" ").append(std::to_string(pinConnection.second.getId()));
        return result;
    }
    ElectronicConnection deserialize(std::stringstream & strm)
    {
        ElectronicConnection a;
        return a;
    }
    friend bool operator<(const ElectronicConnection & e1,const ElectronicConnection & e2)
    {
        return e1.pinConnection.first < e2.pinConnection.second;
    }
    friend bool operator==(const ElectronicConnection & e1,const ElectronicConnection & e2)
    {
        return e1.pinConnection.first == e2.pinConnection.second;
    }
    friend bool operator!=(const ElectronicConnection & e1,const ElectronicConnection & e2)
    {
        return !(e1 == e2);
    }
};

#endif