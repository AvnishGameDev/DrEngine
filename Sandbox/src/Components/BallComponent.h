#pragma once

#include "DrEngine.h"
#include "NotificationComp.h"

using namespace DrEngine;

class BallComponent : public Component
{
public:

    BallComponent(std::vector<Entity*>& inPaddles)
    {
        paddles = inPaddles;
    }
    
    void BeginPlay() override
    {
        transform = GetOwner()->GetComponentByClass<TransformComponent>();
    }

    void Update(float deltaTime) override
    {
        now = Application::GetMilliseconds();
        
        if (now - last > 100)
        {
            for (auto p : paddles)
            {
                if (Collision::AABB(GetOwner()->GetComponentByClass<CollisionComponent>(), p->GetComponentByClass<CollisionComponent>()))
                {
                    transform->Velocity.SetX(transform->GetVelocity().X() * -1);
                    last = now;
                    Score++;
                }
            }

            if (transform->GetLocation().X() > 800 || transform->GetLocation().X() < 0)
            {
                transform->Velocity.SetX(transform->GetVelocity().X() * -1);
                last = now;
                Score = 0;

                Application::manager->AddEntity()->AddComponent<NotificationComp>("Score Reset!", 1000);
            }
            if (transform->GetLocation().Y() > 580 || transform->GetLocation().Y() < 0)
            {
                transform->Velocity.SetY(transform->GetVelocity().Y() * -1);
                last = now;
            }
        }
    }

    int GetScore() const { return Score; };
private:
    int Score{0};
    
    Uint32 last, now;
    
    std::vector<Entity*> paddles;
    TransformComponent* transform;
};