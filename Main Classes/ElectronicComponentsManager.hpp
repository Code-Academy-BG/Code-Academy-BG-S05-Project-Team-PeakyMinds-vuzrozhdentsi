#ifndef ELECTRONIC_COMPONENT_MANAGER_H
#define ELECTRONIC_COMPONENT_MANAGER_H

#include "ElectronicComponent.hpp"
#include <string>
#include <vector>
#include <set> // to keep unique values??

// IMPORTANT
// This class is only committed and pushed to repo as per CA request for visibility on the progress. 


class ElectronicComponentsManager
{
private:
    ElectronicComponentsManager();
    std::vector<ElectronicComponent> elCoDb;
public:
   
   static ElectronicComponentsManager * getIstance();
   std::vector<ElectronicComponent> getElCoDb() const;
   const ElectronicComponent getElectronicComponent() const;
   void addElectronicComponent (ElectronicComponent e);
   void updateElectronicComponent (ElectronicComponent e);
   void deleteElectronicComponent (ElectronicComponent e);
};

#endif