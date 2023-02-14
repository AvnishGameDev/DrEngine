#pragma once
#include <bitset>
#include <vector>

#include "Components/CollisionComponent.h"
#include "Entity.h"
#include "../Collision.h"

namespace DrEngine::ECS
{
    
    class DRENGINE_API Manager
    {
    public:

        template<class T = Entity, typename... Args>
        T* AddEntity(Args... args)
        {
            T* e = new T(args...);
            EntityBitset[currentEntitySlot++] = true;
            Entities.push_back(Utils::Cast<Entity>(e));
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
        
        void Update(float deltaTime)
        {
            for (auto e : Entities)
            {
                if (e)
                    e->Update(deltaTime);
            }
            
            for (const auto c : CollisionComps)
            {
                for (const auto c2 : CollisionComps)
                {
                    if (c != c2)
                    {
                        if (Collision::AABB(c, c2))
                        {
                            c->GetOwner()->OnCollision(CollisionData(c2->GetOwner()));
                        }
                    }
                }
            }
        }

        void Draw(float deltaTime)
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
                e->Draw(deltaTime);
            }
            for (auto e : PropEntities)
            {
                e->Draw(deltaTime);
            }
            for (auto e : PlayerEntities)
            {
                e->Draw(deltaTime);
            }
            for (auto e : PlayerCompEntities)
            {
                e->Draw(deltaTime);
            }
        }

        void AddCollisionComp(CollisionComponent* inComp)
        {
            CollisionComps.push_back(inComp);
        }
        
    private:
        
        std::bitset<MAX_ENTITIES> EntityBitset;

        std::vector<Entity*> Entities;
        std::vector<CollisionComponent*> CollisionComps;

        int currentEntitySlot{0};
    
    };
}
