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
            SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), R, G, B, 255);
            SDL_RenderFillRect(Application::renderer->GetSDLRenderer(), &rect);
        }

        SDL_Rect* GetRect() { return &rect; };
        
    private:

        int R,G,B;
        
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
