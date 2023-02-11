#pragma once

#include "DrEngine.h"

using namespace DrEngine;

class PaddleController : public Component
{
public:
    void BeginPlay() override
    {
        transform = GetOwner()->GetComponentByClass<TransformComponent>();
    }
    
    void Update() override
    {
        transform->Location = Vector2D(transform->GetLocation().X(), Application::inputManager->GetMousePos().Y());
    }
private:
    TransformComponent* transform;
};