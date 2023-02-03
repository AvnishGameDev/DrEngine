#pragma once

#include "Component.h"
#include "ECS.h"
#include "../Log.h"

namespace DrEngine::ECS
{
    class DRENGINE_API Entity
    {
    public:
        Entity()
        {
            
        }
        
        ~Entity()
        {
            
        }

        void BeginPlay()
        {
            for (auto c : Components)
            {
                if (c)
                    c->BeginPlay();
            }
        }

        void Update()
        {
            for (auto c : Components)
            {
                if (c)
                    c->Update();
            }
        }
        
        template<class T, typename... Args>
        T* AddComponent(Args... args)
        {
            auto c = new T(args...);
            Components.push_back(c);
            return c;
        }

        template<class T>
        T* GetComponentByClass()
        {
            for (auto c : Components)
            {
                if (Utils::IsType<T>(c))
                {
                    return c;
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

    private:

        std::vector<Component*> Components;
        
    };
}
