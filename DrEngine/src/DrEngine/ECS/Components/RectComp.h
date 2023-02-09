#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

#include "TransformComponent.h"
#include "../ECS.h"

namespace DrEngine::ECS
{
    class DRENGINE_API RectComp : public Component
    {
    public:
        RectComp(TransformComponent* inTransform)
        {
            transform = inTransform;
        }

        RectComp()
        {
            //transform = GetOwner()->GetComponentByClass<TransformComponent>();
        }
        
        ~RectComp()
        {
            
        }

        void BeginPlay() override
        {
            
        }

        void Update() override
        {
            if (transform)
            {
                rect.x = transform->GetLocation().X();
                rect.y = transform->GetLocation().Y();
                rect.w = transform->GetScale().X();
                rect.h = transform->GetScale().Y();
            }
        }

        void Draw() override
        {
            float R, G, B;
            R = 0;
            G = SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
            B = SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
            
            SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), R, G, B, 255);
            SDL_RenderFillRect(Application::renderer->GetSDLRenderer(), &rect);
        }

        SDL_Rect* GetRect() { return &rect; };
        
    private:
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
