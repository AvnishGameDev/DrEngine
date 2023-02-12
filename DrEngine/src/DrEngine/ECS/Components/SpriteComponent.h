#pragma once

#include "../ECS.h"

#include "SDL_image.h"

namespace DrEngine::ECS
{
    class DRENGINE_API SpriteComponent : public Component
    {
    public:
        SpriteComponent(const std::string& img_path)
        {
            imgPath = img_path;
            auto surface = IMG_Load(imgPath.c_str());
            if (!surface)
            {
                DE_ERROR("Failed to Create Surface from imgPath");
            }

            texture = SDL_CreateTextureFromSurface(Application::renderer->GetSDLRenderer(), surface);
            if (!texture)
            {
                DE_ERROR("Failed to Create Texture from Surface");
            }

            SDL_FreeSurface(surface);
        }
        
        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Failed to get Transform Component");
            }
        }

        void Draw() override
        {
            SDL_Rect rect;
            rect.x = transform->GetLocation().X();
            rect.y = transform->GetLocation().Y();
            rect.w = transform->GetScale().X();
            rect.h = transform->GetScale().Y();
            
            if (texture)
            {
                SDL_RenderCopy(Application::renderer->GetSDLRenderer(), texture, nullptr, &rect);
            }
            else
            {
                DE_ERROR("texture not valid!");
            }
        }
    private:

        TransformComponent* transform{nullptr};
        
        SDL_Texture* texture;
        std::string imgPath;
    };
}