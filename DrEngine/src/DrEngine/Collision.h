#pragma once

#include "Core.h"

namespace DrEngine
{
    namespace ECS
    {
        class CollisionComponent;
    }
    
    class DRENGINE_API Collision
    {
    public:
        static bool AABB(const ECS::CollisionComponent* colA, const ECS::CollisionComponent* colB);
    };
}
