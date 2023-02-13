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

        void Draw(float deltaTime) override
        {
            SDL_Rect rect;
            rect.x = static_cast<int>(transform->GetLocation().X());
            rect.y = static_cast<int>(transform->GetLocation().Y());
            rect.w = static_cast<int>(transform->GetScale().X());
            rect.h = static_cast<int>(transform->GetScale().Y());
            
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