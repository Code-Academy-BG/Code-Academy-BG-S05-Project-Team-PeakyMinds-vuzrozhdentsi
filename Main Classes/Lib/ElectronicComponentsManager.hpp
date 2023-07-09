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
    void addComponent(const ElectronicComponent &h)
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
        FileManager fm(libraryPathName);
        std::cout << "EC Library is loading\n";
        if (fm.get().peek() != fm.get().eof())
        {
            while (!(fm.get() >> std::ws).eof())
            {
                librarySet.emplace(ElectronicComponent(fm.get()));
                if (fm.get().fail())
                {
                    break;
                }
            }
        }
        else
        {
            std::cout << "file is empty \n";
        }
        std::cout << "EC Library is loaded\n";
        return librarySet;
    }
    bool checkByName(const std::string &wantedID)
    {
        if (librarySet.empty())
        {
            return false;
        }

        return !(librarySet.end() == std::find_if(librarySet.begin(), librarySet.end(), [&](const ElectronicComponent &hc)
                                                  { return hc.getId() == wantedID; }));
    }
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