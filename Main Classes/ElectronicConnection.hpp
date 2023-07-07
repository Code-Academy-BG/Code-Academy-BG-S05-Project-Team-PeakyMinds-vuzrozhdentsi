#ifndef ELECTRONIC_CONNECTION_H
#define ELECTRONIC_CONNECTION_H

#include <string>
#include <sstream>
#include "ElectronicComponent.hpp"
#include "HardwareComponent.hpp"

class HardwareComponent;
class ElectronicConnection
{
private:
    using ElectronicComponentBoardOrderNumber = int;
    using PinId = Pin;
    std::pair<ElectronicComponentBoardOrderNumber, ElectronicComponentBoardOrderNumber> electronicComponentConnection;
    std::pair<PinId, PinId> pinConnection;

public:
    ElectronicConnection() : electronicComponentConnection{}, pinConnection{} {};
    ElectronicConnection(const ElectronicComponentBoardOrderNumber &e1, const PinId &pin1, const ElectronicComponentBoardOrderNumber &e2, const PinId &pin2)
    {
        electronicComponentConnection.first = e1;
        electronicComponentConnection.second = e2;
        pinConnection.first = pin1;
        pinConnection.second = pin2;
    }
    ElectronicConnection(std::istream &stream)
    {
        stream >> *this;
    }
    // void resetConnection(ElectronicComponent e1,int pinPosition1,ElectronicComponent e2, int pinPostion2);
    std::pair<Pin, Pin> getPinConnection() const
    {
        return this->pinConnection;
    }
    //
    std::string toMachineLevelFormatSting()
    {
        std::string result{""};
        result.append(pinConnection.first.toMachineLevelFormatString()).append(" ").append(pinConnection.second.toMachineLevelFormatString());
        return result;
    };
    std::string toString()
    {
        std::string result{""};
        result.append("(").append(std::to_string(electronicComponentConnection.first)).append(".").append(std::to_string(pinConnection.first.getId())).append(",").append(std::to_string(electronicComponentConnection.second)).append(".").append(std::to_string(pinConnection.second.getId())).append(")");
        return result;
    }

    friend bool operator==(const ElectronicConnection &e1, const ElectronicConnection &e2)
    {
        return e1.pinConnection.first == e2.pinConnection.first && e1.pinConnection.second == e2.pinConnection.second && e1.electronicComponentConnection.first == e2.electronicComponentConnection.first && e1.electronicComponentConnection.second == e2.electronicComponentConnection.second;
    }
    friend bool operator!=(const ElectronicConnection &e1, const ElectronicConnection &e2)
    {
        return !(e1 == e2);
    }
    friend std::ostream &operator<<(std::ostream &stream, const ElectronicConnection &c)
    {
        stream << c.electronicComponentConnection.first << ' ' << c.electronicComponentConnection.second << ' '
               << c.pinConnection.first << ' ' << c.pinConnection.second << ' ';
        return stream;
    };
    friend std::istream &operator>>(std::istream &stream, ElectronicConnection &c)
    {
        stream >> c.electronicComponentConnection.first >> c.electronicComponentConnection.second >> c.pinConnection.first >> c.pinConnection.second;
        return stream;
    }
};

#endif