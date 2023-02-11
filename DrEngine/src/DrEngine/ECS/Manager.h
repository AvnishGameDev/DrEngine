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

        template<typename... Args>
        Entity* AddEntity(Args... args)
        {
            auto* e = new Entity(args...);
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
            std::vector<Entity*> TileEntities;
            std::vector<Entity*> PropEntities;
            std::vector<Entity*> PlayerEntities;
            std::vector<Entity*> PlayerCompEntities;
            for (auto e : Entities)
            {
                switch (e->GetBatch())
                {
                case Tile:
                    TileEntities.push_back(e);
                    break;
                case Prop:
                    PropEntities.push_back(e);
                    break;
                case Player:
                    PlayerEntities.push_back(e);
                    break;
                case PlayerComp:
                    PlayerCompEntities.push_back(e);
                    break;
                }
            }

            /* Batch Rendering */

            for (auto e : TileEntities)
            {
                e->Draw();
            }
            for (auto e : PropEntities)
            {
                e->Draw();
            }
            for (auto e : PlayerEntities)
            {
                e->Draw();
            }
            for (auto e : PlayerCompEntities)
            {
                e->Draw();
            }
        }
        
    private:
        
        std::bitset<MAX_ENTITIES> EntityBitset;

        std::vector<Entity*> Entities;

        int currentEntitySlot{0};
    
    };
}
