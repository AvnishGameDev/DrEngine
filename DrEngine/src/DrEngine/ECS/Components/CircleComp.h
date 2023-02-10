#pragma once

#include "../ECS.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

class CircleComp : public Component
{
public:
    CircleComp()
    {
        
    }
    ~CircleComp()
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
    
    void Draw() override
    {
        int X, Y;
        X = transform->GetLocation().X();
        Y = transform->GetLocation().Y();
        
        DrawCircle(Application::renderer->GetSDLRenderer(), X, Y, transform->GetScale().X());
    }
    
private:

    TransformComponent* transform;
    
    void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
    {
        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
            SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
            SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
            SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
            SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
            SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
            SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
            SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
    
};