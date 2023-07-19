#include "Board.hpp"

#include<memory>
#include<vector>
#include<set>

class BoardFactory
{
private:
    using FactoryRawMaterial = Board;
    using FactoryType = std::shared_ptr<FactoryRawMaterial>;
    using FactoryTypePool = std::set<FactoryType>;
    FactoryTypePool pool;
public:
    BoardFactory(){};
    ~BoardFactory(){};
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