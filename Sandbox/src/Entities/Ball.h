#pragma once

#include "DrEngine.h"

using namespace DrEngine;

class Ball : public Entity
{
public:
    Ball(const std::vector<Entity*>& inPaddles) : Entity("Ball")
    {
        AddComponent<TransformComponent>();
        GetComponentByClass<TransformComponent>()->Location = Vector2D(280, 280);
        GetComponentByClass<TransformComponent>()->Scale = Vector2D(36, 36);
        GetComponentByClass<TransformComponent>()->Velocity = Vector2D(0.28f, -0.28f);
        AddComponent<RectComp>(0, 0, 0)->SetVisibility(false);
        AddComponent<CollisionComponent>();
        AddComponent<BallComponent>(inPaddles);
        AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 28, "Score: 0");
        AddComponent<SpriteComponent>("Assets/Images/ball.png");
    }
    
    ~Ball()
    {
        
    }

    void BeginPlay() override
    {
        Entity::BeginPlay();
        
    }

    void Update(float deltaTime) override
    {
        Entity::Update(deltaTime);
        
    }
};