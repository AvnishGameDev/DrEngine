#pragma once

#include "Component.h"
#include <string>

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
        
        Entity(const std::string& inName, const Batch& inBatch = Player)
        {
            name = inName;
            batch = inBatch;
        }

        Entity(Batch inBatch = Player)
        {
            name = rand();
            batch = inBatch;
        }

        void Destroy() { bActive = false; };

        bool IsInit() const { return bInit; };

        bool IsActive() const { return bActive; };
        
        virtual void BeginPlay()
        {
            bInit = true;
        }

        virtual void Update(float deltaTime)
        {
            for (auto c : Components)
            {
                if (c)
                    c->Update(deltaTime);
            }
        }

        virtual void Draw(float deltaTime)
        {
            for (auto c : Components)
            {
                if (c)
                    c->Draw(deltaTime);
            }
        }
        
        template<class T, typename... Args>
        T* AddComponent(Args... args)
        {
            T* c(new T(std::forward<Args>(args)...));
            c->owner = this;
            std::unique_ptr<Component> uPtr{c};
            Components.emplace_back(std::move(uPtr));
            c->BeginPlay();
            return c;
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

        void SetBatch(Batch inBatch) { batch = inBatch; };
        
    private:
        Batch batch{Player};
        
        std::string name;
        
        std::vector<std::unique_ptr<Component>> Components;

        bool bInit{false};
        bool bActive{true};
        
    };
}
