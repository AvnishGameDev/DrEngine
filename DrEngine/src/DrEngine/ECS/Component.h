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

        void BeginPlay()
        {
            
        }

        void Update()
        {
            DE_INFO("Component Update");
        }
    };
}
