#pragma once
#include <bitset>
#include <vector>

#include "ECS.h"
#include "Entity.h"

namespace DrEngine::ECS
{
    
    class DRENGINE_API Manager
    {
    public:

        Entity* AddEntity()
        {
            auto* e = new Entity();
            EntityBitset[currentEntitySlot++] = true;
            Entities.push_back(e);
            e->BeginPlay();
            return e;
        }
        
        void DestroyEntity(Entity*& e)
        {
            for (auto itr = Entities.begin(); itr < Entities.end(); ++itr)
            {
                if (*itr == e)
                {
                    EntityBitset[std::distance(Entities.begin(), itr)] = false;
                    Entities.erase(itr);
                    delete e;
                    e = nullptr;
                }
            }
        }
        
        void Update()
        {
            for (auto e : Entities)
            {
                if (e)
                    e->Update();
            }
        }

        void Draw()
        {
            for (auto e : Entities)
            {
                if (e)
                    e->Draw();
            }
        }
        
    private:
        
        std::bitset<MAX_ENTITIES> EntityBitset;

        std::vector<Entity*> Entities;

        int currentEntitySlot{0};
    
    };
}
