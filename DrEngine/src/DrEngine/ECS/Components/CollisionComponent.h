#pragma once

#include "../ECS.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

namespace DrEngine::ECS
{
    class DRENGINE_API CollisionComponent : public Component
    {
    public:
        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_WARN("TransformComponent not found");
            }

            Application::Colliders.push_back(this);
        }

        TransformComponent* GetTransform() const { return transform; };

    private:
        TransformComponent* transform{nullptr};
    };
}