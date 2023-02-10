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
            name = rand();
        }
        
        Entity(std::string inName)
        {
            name = inName;
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

    private:

        std::string name;
        
        std::vector<Component*> Components;
        
    };
}
