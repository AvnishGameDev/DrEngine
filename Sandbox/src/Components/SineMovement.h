#pragma once

#include "DrEngine.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

class SineMovement : public Component
{
public:
    SineMovement(TransformComponent* inTransform)
    {
        transform = inTransform;
    }
    
    ~SineMovement()
    {
        
    }

    void BeginPlay() override
    {
        
    }

    void Update() override
    {
        const float posX = 700.0f  / 2.0f + SDL_sinf(SDL_GetTicks() / 1000.0f * 3.18378f) * (700.0f / 2.0f);
        const float posY = 500.0f / 2.0f + SDL_cosf(SDL_GetTicks() / 1000.0f) * (500.0f / 2.0f);

        transform->Location = Vector2D(posX, posY);
    }

private:
    TransformComponent* transform;
};