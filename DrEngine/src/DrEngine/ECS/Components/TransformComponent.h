#pragma once

#include "../ECS.h"
#include "../../Math/Vector2D.h"

namespace DrEngine::ECS
{
    class DRENGINE_API TransformComponent : public Component
    {
    public:
        TransformComponent(Vector2D Loc = Vector2D::Zero(), Vector2D Sc = Vector2D::Zero(), Vector2D Vel = Vector2D::Zero())
        {
            Location = Loc;
            Scale = Sc;
            Velocity = Vel;
        }

        ~TransformComponent() override
        {
            
        }

        Vector2D GetLocation() const { return Location; };
        Vector2D GetScale() const { return Scale; };
        Vector2D GetVelocity() const { return Velocity; };
    private:
        Vector2D Location;
        Vector2D Scale;
        Vector2D Velocity;
    };
}
