#ifndef ELECTRONIC_COMPONENT_MANAGER_H
#define ELECTRONIC_COMPONENT_MANAGER_H
#include <string>
#include <vector>
#include <set> // to keep unique values
#include "FileManager.hpp"
#include "ElectronicComponent.hpp"
class ElectronicComponentsManager
{
private:
    static const std::string NO_SUCH_DESIGN;

    static std::unique_ptr<ElectronicComponentsManager> mngr;
   
    ElectronicComponentsManager(const ElectronicComponentsManager &) = delete;
    ElectronicComponentsManager(ElectronicComponentsManager &&) = delete;
    ElectronicComponentsManager &operator=(const ElectronicComponentsManager &) = delete;
    ElectronicComponentsManager &operator=(ElectronicComponentsManager &&) = delete;

    using libraryContainer = std::set<ElectronicComponent>;
    libraryContainer librarySet;

public:
    ElectronicComponentsManager(){};
    ~ElectronicComponentsManager(){};

    libraryContainer &getLibrary()
    {
        return librarySet;
    };
    const ElectronicComponent &getComponentById(const std::string &wantedID)
    {
        if (checkByName(wantedID))
        {
            return *(std::find_if(librarySet.begin(), librarySet.end(), [&](const ElectronicComponent &hc)
                                  { return hc.getId() == wantedID; }));
        }
        throw std::invalid_argument(NO_SUCH_DESIGN);
    };
    void addHardwareComponent(const ElectronicComponent &h)
    {
        for (auto iter = librarySet.cbegin(); iter != librarySet.cend(); iter++)
        {
            if (*iter == h)
            {
                return;
            }
        }
        librarySet.insert(h);
    };
    libraryContainer load(const std::string &libraryPathName)
    {
        FileManager fm(libraryPathName);
        while (!fm.get().eof())
        {
            librarySet.emplace(ElectronicComponent(fm.get()));
        }
        return librarySet;
    }
    bool checkByName(const std::string &wantedID)
    {
        return !(librarySet.end() == std::find_if(librarySet.begin(), librarySet.end(), [&](const ElectronicComponent &hc)
                                                  { return hc.getId() == wantedID; }));
    }
    void save(const std::string &libraryPathName)
    {
        FileManager fm(libraryPathName);
    
        for(auto iter = librarySet.begin(); iter != librarySet.end(); iter++)
        {
            fm.get() << *iter; 
        }
    }
};

const std::string ElectronicComponentsManager::NO_SUCH_DESIGN{"There is no such design"};

#endif