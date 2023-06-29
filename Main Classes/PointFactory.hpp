#ifndef POINT_FACTORY_HPP
#define POINT_FACTORY_HPP
#include"Point.hpp"

#include<memory>
#include<vector>
#include<set>

class PointFactory
{ 
public:
    using FactoryRawMaterial = Point;
    using FactoryType = std::shared_ptr<FactoryRawMaterial>;
private:
    using FactoryTypePool = std::set<FactoryType>;
    FactoryTypePool pool;
public:

    PointFactory(){};
    ~PointFactory(){};
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