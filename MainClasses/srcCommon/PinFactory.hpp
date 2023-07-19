#ifndef PIN_FACTORY_HPP
#define PIN_FACTORY_HPP

#include"Pin.hpp"

#include<memory>
#include<vector>
#include<set>

class PinFactory
{
public:
    using FactoryRawMaterial = Pin;
    using FactoryType = std::shared_ptr<FactoryRawMaterial>;

private:
    using FactoryTypePool = std::set<FactoryType>;
    FactoryTypePool pool;
public:
    PinFactory(){};
    ~PinFactory(){};
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