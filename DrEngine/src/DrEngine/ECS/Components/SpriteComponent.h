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
            texture = new Texture(img_path);
        }
        
        ~SpriteComponent()
        {
            texture->Destroy();
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
            if (texture)
            {
                Application::GetRenderer()->RenderTexture(transform->GetLocation(), transform->GetScale(), texture);
            }
            else
            {
                DE_ERROR("texture not valid!");
            }
        }
    private:

        TransformComponent* transform{nullptr};

        Texture* texture;
    };
}