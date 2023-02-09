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
        
    private:
        TransformComponent* transform;

        SDL_Rect rect;
    };
}
