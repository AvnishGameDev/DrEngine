#pragma once
#include <bitset>
#include <vector>

#include "ECS.h"

namespace DrEngine::ECS
{
    class Entity;
    
    class DRENGINE_API Manager
    {
    public:

        Entity* AddEntity();
        void DestroyEntity(Entity*& e);
        
    private:
        
        std::bitset<MAX_ENTITIES> EntityBitset;

        std::vector<Entity*> Entities;

        int currentEntitySlot{0};
    
    };
}
