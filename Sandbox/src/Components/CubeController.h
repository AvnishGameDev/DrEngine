#pragma once

#include "DrEngine.h"

using namespace DrEngine::ECS;

class CubeController : public Component
{
public:
    void BeginPlay() override
    {
        
    }

    void Update() override
    {
        Vector2D Loc = GetOwner()->GetComponentByClass<TransformComponent>()->Location;
        
        const Uint8* Keys = SDL_GetKeyboardState(NULL);
        if (Keys[SDL_SCANCODE_W])
        {
            Loc.SetY(Loc.Y() - 1);
        }
        if (Keys[SDL_SCANCODE_A])
        {
            Loc.SetX(Loc.X() - 1);
        }
        if (Keys[SDL_SCANCODE_S])
        {
            Loc.SetY(Loc.Y() + 1);
        }
        if (Keys[SDL_SCANCODE_D])
        {
            Loc.SetX(Loc.X() + 1);
        }

        GetOwner()->GetComponentByClass<TransformComponent>()->Location = Loc;
    }
private:
    
};