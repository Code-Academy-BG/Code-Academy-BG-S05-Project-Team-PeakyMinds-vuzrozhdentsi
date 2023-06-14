#ifndef ELECTRONIC_CONNECTION_H
#define ELECTRONIC_CONNECTION_H

#include <string>
#include "ElectronicComponent.hpp"


class ElectronicConnection
{
private:
    std::pair<ElectronicComponent,ElectronicComponent> electronicComponentConnection;
    std::pair<Pin,Pin> pinConnection;
public:
    ElectronicConnection();
    ElectronicConnection(ElectronicComponent e1,int pinPosition1,ElectronicComponent e2, int pinPostion2);
    void resetConnection(ElectronicComponent e1,int pinPosition1,ElectronicComponent e2, int pinPostion2);
    std::string toString();
};

#endif