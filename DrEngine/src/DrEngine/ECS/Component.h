#pragma once

#include "ECS.h"
#include "../Log.h"

namespace DrEngine::ECS
{
    class Entity;
    
    class DRENGINE_API Component
    {
    public:
        Component()
        {
        }

        virtual ~Component()
        {
            
        }

        virtual void BeginPlay()
        {
            
        }

        virtual void Update()
        {
            
        }

        virtual void Draw()
        {
            
        }

        Entity* GetOwner() const { return owner; };

        
        Entity* owner;
    };
}
