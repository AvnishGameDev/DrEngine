#pragma once

#include "DrEngine.h"

using namespace DrEngine::ECS;

class ScaleBlend : public Component
{
public:

    ScaleBlend(Vector2D inMaxSize = Vector2D::Zero())
    {
        MaxSize = inMaxSize;
    }
    
    void BeginPlay() override
    {
        transform = GetOwner()->GetComponentByClass<TransformComponent>();
        if (!transform)
        {
            DE_WARN("TransformComponent not found");
        }
        if (transform)
        {
            if (MaxSize == Vector2D::Zero())
            {
                MaxSize = transform->GetScale();
            }
        }
    }

    void Update(float deltaTime) override
    {
        Vector2D Scale;
        Scale.SetX(SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * MaxSize.X()));
        Scale.SetY(SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * MaxSize.Y()));

        transform->Scale = Scale;
    }
    
private:

    Vector2D MaxSize;
    
    TransformComponent* transform;
};