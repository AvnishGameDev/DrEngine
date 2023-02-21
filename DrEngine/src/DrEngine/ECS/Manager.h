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
            std::unique_ptr<Entity> uPtr{e};
            Entities.emplace_back(std::move(uPtr));
            e->BeginPlay();
            return e;
        }
        
        void Update(float deltaTime)
        {
            for (auto e : Entities)
            {
                if (e != nullptr)
                {
                    if (e->IsInit())
                        e->Update(deltaTime);
                }
            }
            
            for (const auto c : CollisionComps)
            {
                for (const auto c2 : CollisionComps)
                {
                    if (c != c2)
                    {
                        if (Collision::AABB(c, c2))
                        {
                            c->OnCollision(CollisionData(c2->GetOwner()));
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
                if (e)
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
            }

            /* Batch Rendering */

            for (auto e : TileEntities)
            {
                if (e)
                    e->Draw(deltaTime);
            }
            for (auto e : PropEntities)
            {
                if (e)
                    e->Draw(deltaTime);
            }
            for (auto e : PlayerEntities)
            {
                if (e)
                    e->Draw(deltaTime);
            }
            for (auto e : PlayerCompEntities)
            {
                if (e)
                    e->Draw(deltaTime);
            }
        }

        void Refresh()
        {
            Entities.erase(std::remove_if(
                std::begin(Entities),
                std::end(Entities),
                [](const std::unique_ptr<Entity>& inEntity)
                {
                    return !inEntity->IsActive();
                }
                ),
                std::end(Entities)
                );
        }

        void AddCollisionComp(CollisionComponent* inComp)
        {
            CollisionComps.push_back(inComp);
        }
        
    private:
        
        std::vector<std::unique_ptr<Entity>> Entities;
        std::vector<CollisionComponent*> CollisionComps;

        int currentEntitySlot{0};
    
    };
}
