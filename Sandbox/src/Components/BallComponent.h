#pragma once

#include "DrEngine.h"

using namespace DrEngine;

class BallComponent : public Component
{
public:

    BallComponent(std::vector<Entity*> inPaddles)
    {
        paddles = inPaddles;
    }
    
    void BeginPlay() override
    {
        transform = GetOwner()->GetComponentByClass<TransformComponent>();
    }

    void Update() override
    {
        for (auto p : paddles)
        {
            if (Collision::AABB(GetOwner()->GetComponentByClass<CollisionComponent>(), p->GetComponentByClass<CollisionComponent>()))
            {
                transform->Velocity.SetX(transform->GetVelocity().X() * -1);
            }
        }

        if (transform->GetLocation().X() > 800 || transform->GetLocation().X() < 0)
        {
            transform->Velocity.SetX(transform->GetVelocity().X() * -1);
        }
        if (transform->GetLocation().Y() > 580 || transform->GetLocation().Y() < 0)
        {
            transform->Velocity.SetY(transform->GetVelocity().Y() * -1);
        }
    }
private:
    std::vector<Entity*> paddles;
    TransformComponent* transform;
};