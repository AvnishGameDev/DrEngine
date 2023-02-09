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
        }
        
        ~RectComp()
        {
            
        }

        void BeginPlay() override
        {
            
        }

        void Update() override
        {
            rect.x = transform->GetLocation().X();
            rect.y = transform->GetLocation().Y();
            rect.w = transform->GetScale().X();
            rect.h = transform->GetScale().Y();
        }

        void Draw() override
        {                                                                   
            //SDL_SetRenderDrawColor(GetWindow()->GetRenderer()->GetSDLRenderer(), R, G, B, 255);
            //SDL_RenderFillRect(GetWindow()->GetRenderer()->GetSDLRenderer(), &rect);
            //SDL_RenderPresent(GetWindow()->GetRenderer()->GetSDLRenderer());
        }

        SDL_Rect* GetRect() { return &rect; };
        
    private:
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
