#pragma once

#include "DrEngine.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

enum TrigFunc
{
    Sin,
    Cos,
    Tan
};

class TrigMovement : public Component
{
public:
    TrigMovement(TrigFunc inTrig = Sin, bool inReverse = false)
    {
        trigFunc = inTrig;
        bReverse = inReverse;
    }
    
    ~TrigMovement()
    {
        
    }

    void BeginPlay() override
    {
        transform = GetOwner()->GetComponentByClass<TransformComponent>();
        if (!transform)
        {
            DE_WARN("TransformComponent not found");
        }
    }

    void Update() override
    {
        float posX, posY;
        
        switch (trigFunc)
        {
        case Sin:
            posX = 700.0f  / 2.0f + SDL_sinf(SDL_GetTicks() / 1000.0f * 3.18378f) * (700.0f / 2.0f);
            posY = 500.0f / 2.0f + SDL_sinf(SDL_GetTicks() / 1000.0f) * (500.0f / 2.0f);
            break;
        case Cos:
            posX = 700.0f  / 2.0f + SDL_cosf(SDL_GetTicks() / 1000.0f * 3.18378f) * (700.0f / 2.0f);
            posY = 500.0f / 2.0f + SDL_cosf(SDL_GetTicks() / 1000.0f) * (500.0f / 2.0f);
            break;
        case Tan:
            posX = 700.0f  / 2.0f + SDL_tanf(SDL_GetTicks() / 1000.0f * 3.18378f) * (700.0f / 2.0f);
            posY = 500.0f / 2.0f + SDL_tanf(SDL_GetTicks() / 1000.0f) * (500.0f / 2.0f);
            break;
        }

        if (transform)
        {
            if (bReverse)
                transform->Location = Vector2D(posY, posX);
            else
                transform->Location = Vector2D(posX, posY);
        }
    }
    
private:
    TrigFunc trigFunc;

    bool bReverse;
    
    TransformComponent* transform;
};