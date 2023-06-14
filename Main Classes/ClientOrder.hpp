#ifndef POINT_H
#define POINT_H

#include "HardwareComponent.hpp"
#include "ElectronicComponent.hpp"
#include <string>
#include <vector>
class ClientOrder
{
enum class Status{};
enum class Priority{};


private:
    int id;
    Status status;
    Priority priority;
    std::vector<HardwareComponent> hardwareComponents;
    std::vector<ElectronicComponent> electronicComponents;
public:
    ClientOrder();
};

#endif