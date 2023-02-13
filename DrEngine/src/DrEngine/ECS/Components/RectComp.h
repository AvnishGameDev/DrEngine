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

        void Draw(float deltaTime) override
        {
            if (bPulse)
            {
                R = 0;
                G = static_cast<int>(SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
                B = static_cast<int>(SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
            }

            if (bVisible)
            {
                Application::GetRenderer()->RenderRect(transform->GetLocation(), transform->GetScale(), Color(R, G, B));
            }
        }

        void SetVisibility(bool inVal) { bVisible = inVal; };
        
    private:

        bool bVisible{true};
        bool bPulse{false};
        
        int R,G,B;
        
        TransformComponent* transform;
    };
}
