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
            SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), 0, 255*0.68, 255, 255);
            SDL_RenderFillRect(Application::renderer->GetSDLRenderer(), &rect);
        }

        SDL_Rect* GetRect() { return &rect; };
        
    private:
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
