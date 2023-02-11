#pragma once

#include "Component.h"
#include "ECS.h"
#include "../Log.h"

namespace DrEngine::ECS
{
    enum Batch
    {
        Tile,       // Ground, most back
        Prop,       // Above Ground
        Player,     // Above Props and Ground
        PlayerComp  // Above everything
    };
    
    class DRENGINE_API Entity
    {
    public:
        
        Entity(std::string inName, Batch inBatch = Player)
        {
            name = inName;
            batch = inBatch;
        }

        Entity(Batch inBatch = Player)
        {
            name = rand();
            batch = inBatch;
        }
        
        ~Entity()
        {
            
        }

        void BeginPlay()
        {
            
        }

        void Update()
        {
            for (auto c : Components)
            {
                if (c)
                    c->Update();
            }
        }

        void Draw()
        {
            for (auto c : Components)
            {
                if (c)
                    c->Draw();
            }
        }
        
        template<class T, typename... Args>
        T* AddComponent(Args... args)
        {
            auto* c = new T(args...);
            c->owner = this;
            c->BeginPlay();
            Components.push_back(c);
            return c;
        }

        void RemoveComponent(Component* c)
        {
            for (auto itr = Components.begin(); itr < Components.end(); ++itr)
            {
                if (*itr == c)
                {
                    Components.erase(itr);
                }
            }
        }
        
        template<class T>
        void RemoveComponentByClass()
        {
            for (auto itr = Components.begin(); itr < Components.end(); ++itr)
            {
                if (Utils::IsType<T>(*itr))
                {
                    Components.erase(itr);
                }
            }
        }

        template<class T>
        T* GetComponentByClass()
        {
            for (auto c : Components)
            {
                if (Utils::IsType<T>(c))
                {
                    return Utils::Cast<T>(c);
                }
            }
            return nullptr;
        }

        template<class T>
        std::vector<T*> GetAllComponentsByClass()
        {
            std::vector<T*> ClassComponents;
            for (auto c : Components)
            {
                if (Utils::IsType<T>(c))
                {
                    ClassComponents.push_back(Utils::Cast<T>(c));
                }
            }
            return ClassComponents;
        }

        std::string GetName() const { return name; };

        Batch GetBatch() const { return batch; };
        
    private:

        Batch batch;
        
        std::string name;
        
        std::vector<Component*> Components;
        
    };
}
