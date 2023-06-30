#ifndef ELECTRONIC_COMPONENT_FACTORY_HPP
#define ELECTRONIC_COMPONENT_FACTORY_HPP

#include"ElectronicComponent.hpp"

#include<memory>
#include<vector>
#include<set>

class ElectronicComponentFactory
{
public:
    using FactoryRawMaterial = ElectronicComponent;
    using FactoryType = std::shared_ptr<FactoryRawMaterial>;

private:
    using FactoryTypePool = std::set<FactoryType>;
    FactoryTypePool pool;
public:
    ElectronicComponentFactory(){};
    ~ElectronicComponentFactory(){};
    FactoryRawMaterial& getInstance(const FactoryRawMaterial & obj)
    {
        for (const FactoryType & pointer : pool)
        {
            if(*pointer == obj){
                return *pointer;
            }
        }
        return *(getInstancePointer(obj));    
    }
    
    FactoryType getInstancePointer(const FactoryRawMaterial & obj)
    {
        for (const FactoryType & pointer : pool)
        {
            if(*pointer == obj){
                return pointer;
            }
        }
        FactoryType newPoint = std::make_shared<FactoryRawMaterial>(obj);
        pool.insert(newPoint);
        return getInstancePointer(obj);
    }
};

#endif