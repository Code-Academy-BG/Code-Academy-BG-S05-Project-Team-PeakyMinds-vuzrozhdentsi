#ifndef HARDWARE_COMPONENT_MANAGER_H
#define HARDWARE_COMPONENT_MANAGER_H

#include "HardwareComponent.hpp"
#include <string>
#include <vector>
#include <set> // to keep unique values
class HardwareComponentsManager
{
private:
    HardwareComponentsManager();
    std::vector<HardwareComponent> elCoDb;
public:
   
   static HardwareComponentsManager * getIstance();
   std::vector<HardwareComponent> getElCoDb() const;
   const HardwareComponent getElectronicComponent() const;
   void addElectronicComponent (HardwareComponent h);
   void updateElectronicComponent (HardwareComponent h);
   void deleteElectronicComponent (HardwareComponent h);
};

#endif