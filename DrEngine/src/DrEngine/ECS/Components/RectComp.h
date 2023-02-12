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

        RectComp(bool inPulse)
        {
            bPulse = inPulse;
        }
        
        RectComp(int inR = 0, int inG = 255, int inB = 255)
        {
            R = inR;
            G = inG;
            B = inB;
        }
        
        ~RectComp()
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
            if (bPulse)
            {
                R = 0;
                G = SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
                B = SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
            }

            if (bVisible)
            {
                SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), R, G, B, 255);
                SDL_RenderFillRect(Application::renderer->GetSDLRenderer(), &rect);
            }
        }

        void SetVisibility(bool inVal) { bVisible = inVal; };
        SDL_Rect* GetRect() { return &rect; };
        
    private:

        bool bVisible{true};
        bool bPulse{false};
        
        int R,G,B;
        
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
