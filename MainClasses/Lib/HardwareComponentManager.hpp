#ifndef HARDWARE_COMPONENT_MANAGER_H
#define HARDWARE_COMPONENT_MANAGER_H

#include "..\srcCommon\HardwareComponent.hpp"
#include <string>
#include <vector>
#include <set> // to keep unique values
#include "..\srcCommon\FileManager.hpp"
class HardwareComponentsManager
{
private:
    static const std::string NO_SUCH_DESIGN;

    static std::unique_ptr<HardwareComponentsManager> mngr;
    HardwareComponentsManager(const HardwareComponentsManager &) = delete;
    HardwareComponentsManager(HardwareComponentsManager &&) = delete;
    HardwareComponentsManager &operator=(const HardwareComponentsManager &) = delete;
    HardwareComponentsManager &operator=(HardwareComponentsManager &&) = delete;


    using libraryContainer = std::set<HardwareComponent>;
    libraryContainer librarySet;

public:
    HardwareComponentsManager(){};

    ~HardwareComponentsManager(){};

    libraryContainer &getLibrary()
    {
        return librarySet;
    };
    const HardwareComponent &getHardwareComponent(const std::string &wantedID)
    {
        if (!librarySet.empty() && checkByName(wantedID))
        {
            return *(std::find_if(librarySet.begin(), librarySet.end(), [&](const HardwareComponent &hc)
                                  { return hc.getId() == wantedID; }));
        }
        throw std::invalid_argument(NO_SUCH_DESIGN);
    };
    void addHardwareComponent(const HardwareComponent &h)
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
    libraryContainer &load(const std::string &libraryPathName)
    {
        std::cout << "HC Library is loading\n";
        FileManager fm(libraryPathName);
        
            while (!(fm.get()>>std::ws).eof())
            {
                librarySet.emplace(HardwareComponent(fm.get()));
                if(fm.get().fail()){
                    break;
                }
            }
        
        std::cout << "HC Library is loaded\n";
        return librarySet;
    }
    bool checkByName(const std::string &wantedID)
    {
        if (!librarySet.empty())
        {

            return !(librarySet.end() == std::find_if(librarySet.begin(), librarySet.end(), [&](const HardwareComponent &hc)
                                                      { return hc.getId() == wantedID; }));
        }
        return false;
    }
    const std::string &getHardwareComponentId(const std::string &wantedID)
    {
        if (checkByName(wantedID))
        {
            return wantedID;
        }
        throw std::invalid_argument(NO_SUCH_DESIGN);
    };
    void save(const std::string &libraryPathName)
    {
        FileManager fm(libraryPathName);

        for (auto iter = librarySet.begin(); iter != librarySet.end(); iter++)
        {
            fm.get() << *iter;
        }
    }
};

#endif