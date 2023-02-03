#pragma once

#include "ECS.h"
#include "../Log.h"

namespace DrEngine::ECS
{
    class DRENGINE_API Component
    {
    public:
        Component()
        {
            
        }

        ~Component()
        {
            
        }

        virtual void BeginPlay()
        {
            
        }

        virtual void Update()
        {
            
        }
    };
}
